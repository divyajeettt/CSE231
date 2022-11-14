mkdir ./kernelbuildA

cd ./kernelbuildA

wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.19.8.tar.xz

unxz linux-5.19.8.tar.xz

tar -xvf linux-5.19.8.tar

chown -R $dvgt:$dvgt linux-5.19.8

cd linux-5.19.8

make mrproper

cp ./../../1/1.2/.config .config

make -j$(nproc)