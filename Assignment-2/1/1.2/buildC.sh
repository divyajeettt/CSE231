cp -r ./linux-5.19.8 ./kernelbuildC/linux-5.19.8

cd ./kernelbuildC/linux-5.19.8

make -j$(nproc)