mkdir ./kernelbuild

cd ./kernelbuild

wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.19.8.tar.xz

unxz linux-5.18.9.tar.xz

tar -xvf linux-5.19.8.tar

chown -R $dvgt:$dvgt linux-5.19.8

make mrproper

cp ./1/1.2/.config ./linux-5.19.8/.config

cd linux-5.19.8

make -j$(nproc)