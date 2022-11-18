cp -r ./linux-5.19.8 ./1.2/kernelbuild/A/linux-5.19.8

cd ./1.2/kernelbuild/A/linux-5.19.8

make -j$(nproc)