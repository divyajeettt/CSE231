cp -r ./linux-5.19.8 ./1/1.2/kernelbuild/C/linux-5.19.8

cd ./1/1.2/kernelbuild/C/linux-5.19.8

make -j$(nproc)

echo "Build C done"