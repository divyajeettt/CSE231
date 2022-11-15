cp -r ./linux-5.19.8 ./kernelbuildB/linux-5.19.8

cd ./kernelbuildB/linux-5.19.8

make -j$(nproc)