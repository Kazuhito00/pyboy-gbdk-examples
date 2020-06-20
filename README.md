# pyboy-gbdk-examples
PyBoyとGBDK(GameBoy Developers Kit)の例です。

# Requirement
* Windows
* GBDK:2.9.5
* PyBoy:1.0.0

# Installation
### GBDK
1. GBDK本体を以下リンクよりダウンロード<br>https://sourceforge.net/projects/gbdk/files/gbdk/<br>本サンプルではWindows版([gbdk-2.95-win32.zip](https://sourceforge.net/projects/gbdk/files/gbdk-win32/2.95/gbdk-2.95-win32.zip/download))を使用。
1. 「C:\gbdk」などの任意のフォルダに解凍
1. Windowsのシステム環境変数に「C:\gbdk\bin」を追加 <br>※「C:\gbdk」以外に解凍した場合は、解答場所に合わせてパスを変更要

### PyBoy
1. SDL2をインストール<br>
　Ubuntu： sudo apt install libsdl2-dev<br>
　Fedora： sudo dnf install SDL2-devel<br>
　macOS： brew install sdl2<br>
　Windows： (New-Object Net.WebClient).DownloadFile('https://www.libsdl.org/release/SDL2-devel-2.0.10-VC.zip', 'SDL2-devel-2.0.10-VC.zip')<br>
　       ： Expand-Archive -Force 'SDL2-devel-2.0.10-VC.zip' C:\SDL2\ <br>
　       ： setx PYSDL2_DLL_PATH C:\SDL2\SDL2-2.0.10\lib\x64 <br>
　       ： setx PATH "%PATH%;C:\SDL2\SDL2-2.0.10\lib\x64"<br>
1. PyBoyをpipインストール<br>
python3 -m pip install --upgrade pip<br>
python3 -m pip install pyboy


詳しくは公式の[Installation](https://github.com/Baekalfen/PyBoy/wiki/Installation)を参照

# Usage

# Contents
* 01.hello_world<br>
HEllo World、および文字表示サンプル
* 02.draw_figure<br>
図形描画サンプル
* 03.key_input	キー入力サンプル追加<br>
キー入力サンプル
* 10.game_of_life

# Reference
* [PyBoy公式](https://github.com/Baekalfen/PyBoy)
* [ゲームボーイはまだ終わってない！](http://boy.game-pc7.com/)

# Author
高橋かずひと(https://twitter.com/KzhtTkhs)

# Licence

nlpaug-examples is under [MIT license](LICENSE).
