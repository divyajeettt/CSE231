cp -r ./linux-5.19.8 ./kernelbuildA/linux-5.19.8

cd ./kernelbuildA/linux-5.19.8

make -j$(nproc)