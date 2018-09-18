rd /s/q build
mkdir build
pushd build
cmake -G "Visual Studio 14 2015 Win64" ..
cmake --build . --config debug
popd
