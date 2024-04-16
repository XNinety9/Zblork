# Installation SFML

```
git clone <https://github.com/SFML/SFML.git>
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DCMAKE_OSX_ARCHITECTURES=arm64 ..
make all
sudo make install
```
