import argparse
from pyboy import PyBoy

# [Keyboard key]   [GameBoy equivalant]
#  Up               Up
#  Down             Down
#  Left             Left
#  Right            Right
#  A                A
#  S                B
#  Return           Start
#  Backspace        Select
#  Escape           Quit
#  D                Debug
#  Space            Unlimited FPS
#  Z                Save state
#  X                Load state
#  I                Toggle screen recording
#  ,                Rewind backwards
#  .                Rewind forward

# コマンドライン引数
parser = argparse.ArgumentParser()
parser.add_argument(
    "--filepath", help='gb file path', default='00.ROMs/01.hello_world.gb')
args = parser.parse_args()

filepath = args.filepath

# PyBoy起動
color_palette = [0xd6e895, 0xacc04c, 0x527d3e, 0x264a2e]
pyboy = PyBoy(filepath, color_palette=color_palette)

while not pyboy.tick():
    pass
