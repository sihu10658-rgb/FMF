#!/usr/bin/env bash

# 색상 출력을 위한 변수
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== FMF Smart Build System v1.0 ===${NC}"

# 1. OS 및 아키텍처 실시간 스캔
OS="$(uname -s)"
ARCH="$(uname -m)"
echo -e "🔎 Detected OS   : ${GREEN}$OS${NC}"
echo -e "🔎 Detected Arch : ${GREEN}$ARCH${NC}"

# 2. 사용할 컴파일러 탐색 (clang 우선, 없으면 gcc)
CC="gcc"
if command -v clang &> /dev/null; then
    CC="clang"
fi
echo -e "🛠️  Compiler    : ${GREEN}$CC${NC}"

# 3. 환경에 따른 최적화 플래그 동적 분기
# --generic 인자를 주거나, GitHub Actions(CI=true) 환경일 경우 범용 모드로 전환
if [ "$1" = "--generic" ] || [ "$CI" = "true" ]; then
    echo -e "🌐 [Mode] Generic / CI Mode: ${GREEN}모든 기기 호환 범용 최적화 (-O3)${NC}"
    CFLAGS="-O3"
else
    echo -e "🚀 [Mode] Local Hyper-Drive Mode: ${GREEN}현 하드웨어 맞춤형 극한 최적화 (-march=native)${NC}"
    CFLAGS="-O3 -march=native"
fi

# 4. 컴파일 실행 (C 엔진 -> 네이티브 바인너리)
echo -e "⚡ Building fmf_engine..."
$CC $CFLAGS fmf.c -o fmf_engine -lm

# 5. 결과 확인
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Build Success!${NC} Run with: ./fmf_engine"
else
    echo -e "❌ Build Failed."
    exit 1
fi
