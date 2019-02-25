# Add the standalone toolchain to the search path.
export PATH=$PATH:/home/user/workspace/android/toolchain/bin
export CMAKE_PREFIX_PATH=/opt/Qt5.12/5.12.0/android_armv7/lib/cmake
export PKG_CONFIG_PATH=/home/user/workspace/android/toolchain/lib/pkgconfig
export SYS_ROOT=/home/user/workspace/android/toolchain

# Tell configure what tools to use.
target_host=arm-linux-androideabi
export AR=$target_host-ar
export AS=$target_host-clang
export CC=$target_host-clang
export CXX=$target_host-clang++
export LD=$target_host-ld
export STRIP=$target_host-strip

# Tell configure what flags Android requires.
export CFLAGS="-fPIE -fPIC"
export LDFLAGS="-pie"

mkdir build 2> /dev/null
cd build
cmake .. -DQT_VERSION=5 -DUSE_OPENGLES=TRUE -DQTGSTREAMER_STATIC=ON \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_ANDROID_STANDALONE_TOOLCHAIN=${SYS_ROOT} \
    -DCMAKE_ANDROID_ARM_NEON=ON \
    -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a \
    -DQTGSTREAMER_GST_PLUGINS_INSTALL_DIR=${SYS_ROOT}/lib/gstreamer-1.0 \
    -DBoost_INCLUDE_DIR=${SYS_ROOT}/workspace/Boost-for-Android/build/out/armeabi-v7a/include/boost-1_69 \
    -DCMAKE_INSTALL_PREFIX=${SYS_ROOT}

make -j4