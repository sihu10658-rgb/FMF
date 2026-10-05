# FMF
fast Math function
안녕하세요 이번에 그냥 코드 공개해드리겠습니다 
build.sh:#!/usr/bin/env bash

GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}=== FMF Smart Build System v1.0 ===${NC}"

OS="$(uname -s)"
ARCH="$(uname -m)"
echo -e "🔎 Detected OS   : ${GREEN}$OS${NC}"
echo -e "🔎 Detected Arch : ${GREEN}$ARCH${NC}"

CC="gcc"
if command -v clang &> /dev/null; then
    CC="clang"
fi
echo -e "🛠️  Compiler    : ${GREEN}$CC${NC}"


if [ "$1" = "--generic" ] || [ "$CI" = "true" ]; then
    echo -e "🌐 [Mode] Generic / CI Mode: ${GREEN}모든 기기 호환 범용 최적화 (-O3)${NC}"
    CFLAGS="-O3"
else
    echo -e "🚀 [Mode] Local Hyper-Drive Mode: ${GREEN}현 하드웨어 맞춤형 극한 최적화 (-march=native)${NC}"
    CFLAGS="-O3 -march=native"
fi


echo -e "⚡ Building fmf_engine..."
$CC $CFLAGS fmf.c -o fmf_engine -lm


if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Build Success!${NC} Run with: ./fmf_engine"
else
    echo -e "❌ Build Failed."
    exit 1
fi 


fmf.c:  
