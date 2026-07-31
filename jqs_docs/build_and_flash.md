# Build & flash: GMMK Pro (REV1, ANSI)

Keymap lives at `keyboards/gmmk/pro/rev1/ansi/keymaps/jqs/`.

## One-time environment (already set up on this machine, 2026-07-31)

- ARM toolchain: xPack `arm-none-eabi-gcc` 10.3.1 at `~/tools/xpack-arm-none-eabi-gcc-10.3.1-2.3/`
- QMK CLI: Python venv at `~/tools/qmkvenv/` (`pip install qmk -r requirements.txt`)
- `dfu-util` via Homebrew (`brew install dfu-util`)

To recreate from scratch: download the xPack tarball from
https://github.com/xpack-dev-tools/arm-none-eabi-gcc-xpack/releases, extract to
`~/tools/`, make the venv, and re-run the pip install inside the repo.

## Build

**Every new shell needs the build PATH first** — otherwise `make` fails with
`/bin/sh: 1: qmk: not found` and `No rule to make target`:

```bash
cd /mnt/data/Backup/Code/me/qmk_firmware
source jqs_docs/env.sh       # puts the ARM toolchain + qmk CLI on PATH
make gmmk/pro/rev1/ansi:jqs
```

Output: `gmmk_pro_rev1_ansi_jqs.bin` in the repo root (DFU-suffixed, ready to flash).

A `WARNING: Some git submodules are out of date` banner is expected and harmless —
it refers to submodules for other platforms (LUFA/AVR, pico-sdk/RP2040) that this
STM32 board doesn't use. Only `lib/chibios`, `lib/chibios-contrib`, and
`lib/printf` matter here, and those are synced.

## Flash — no second keyboard needed

The trick is to start the flasher *first*, then put the board in bootloader mode.
The flasher sits and waits, so you never need to type after the keyboard drops out:

```bash
make gmmk/pro/rev1/ansi:jqs:flash    # builds, then prints "Waiting for DFU device"
```

Then press **Fn + `\`** (the `QK_BOOT` key on layer 1). The board disconnects as a
keyboard, re-enumerates as an STM32 DFU device, gets flashed automatically, and
reboots into the new firmware a few seconds later.

Alternatives, if you prefer:
- SSH in from another machine and run the flash command there.
- Manual flash of an existing .bin:
  `dfu-util -a 0 -s 0x08000000:leave -D gmmk_pro_rev1_ansi_jqs.bin`

### If the firmware is too broken to reach Fn+`\`

Hardware bootloader entry: unplug the USB cable, hold **Space + B**, plug back in
while holding. The board enumerates straight into DFU.

### If dfu-util says "Cannot open DFU device" (permissions)

Install QMK's udev rules once (needs your password):

```bash
sudo cp util/udev/*.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

## Keeping the fork up to date

This clone has two remotes: `origin` (the fork, github.com/jqs/qmk_firmware) and
`original` (upstream, github.com/qmk/qmk_firmware). The update flow is:

```bash
git fetch original master      # download upstream history
git merge original/master      # merge it into local master
git push origin master         # publish the result to the fork
```

(`git pull original master` is shorthand for the first two steps.)
