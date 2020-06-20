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


※詳しくは公式の[Installation](https://github.com/Baekalfen/PyBoy/wiki/Installation)を参照

# Usage
```bash
python sample.py --rom 00.ROMs/01.hello_world.gb
```

# Build ※Windows版
各フォルダ配下にある「make.cmd」を実行してください。

# Contents
* 01.hello_world<br>
HEllo World、および文字表示サンプル<br>
![2020-06-20](https://user-images.githubusercontent.com/37477845/85189469-5c5e5980-b2ea-11ea-8ea6-35368492029c.png)
* 02.draw_figure<br>
図形描画サンプル<br>
![2020-06-20 (1)](https://user-images.githubusercontent.com/37477845/85189471-5e281d00-b2ea-11ea-98c1-d1fa0f46b136.png)
* 03.key_input<br>
キー入力サンプル<br>
![2020-06-20 (3)](https://user-images.githubusercontent.com/37477845/85189472-5ec0b380-b2ea-11ea-8fc1-dc60d13e0be5.png)
* 10.game_of_life<br>
ライフゲームサンプル<br>
![2020-06-20 (5)](https://user-images.githubusercontent.com/37477845/85189474-5f594a00-b2ea-11ea-8210-b2c0c6d0c038.png)

# Reference
* [PyBoy公式](https://github.com/Baekalfen/PyBoy)
* [ゲームボーイはまだ終わってない！](http://boy.game-pc7.com/)

# Author
高橋かずひと(https://twitter.com/KzhtTkhs)

# Licence

nlpaug-examples is under [MIT license](LICENSE).
