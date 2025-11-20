#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

clear

echo -e "${CYAN}${BOLD}"
cat << "EOF"
    ╔═══════════════════════════════════════════════════════════╗
    ║                                                           ║
    ║     🐜 → 🏠 → 🏠 → 🏠 → 🎯                              ║
    ║                                                           ║
    ║          AMAZE-D: Where Ants Meet Algorithms             ║
    ║                   DEMO SHOWCASE                          ║
    ║                                                           ║
    ╚═══════════════════════════════════════════════════════════╝
EOF
echo -e "${RESET}\n"

sleep 1

echo -e "${YELLOW}${BOLD}🎬 Demo 1: Simple Path${RESET}"
echo -e "${CYAN}Description: 1 ant, direct connection${RESET}\n"
sleep 1
./amaze-d -v < tests/test_simple.txt
echo ""
read -p "Press Enter to continue..."
clear

echo -e "${YELLOW}${BOLD}🎬 Demo 2: Linear Path with Multiple Ants${RESET}"
echo -e "${CYAN}Description: 3 ants navigating through 2 rooms${RESET}\n"
sleep 1
./amaze-d -v < tests/test.txt
echo ""
read -p "Press Enter to continue..."
clear

echo -e "${YELLOW}${BOLD}🎬 Demo 3: Longer Linear Path${RESET}"
echo -e "${CYAN}Description: 4 ants through 5 rooms${RESET}\n"
sleep 1
./amaze-d -v < tests/test2.txt
echo ""
read -p "Press Enter to continue..."
clear

echo -e "${YELLOW}${BOLD}🎬 Demo 4: Complex Graph${RESET}"
echo -e "${CYAN}Description: 5 ants in a graph with multiple paths${RESET}\n"
sleep 1
./amaze-d -v < tests/test3.txt
echo ""
read -p "Press Enter to continue..."
clear

echo -e "${GREEN}${BOLD}"
cat << "EOF"
    ╔═══════════════════════════════════════════════════════════╗
    ║                                                           ║
    ║                  ✨ DEMO COMPLETE ✨                      ║
    ║                                                           ║
    ║              Thank you for watching!                      ║
    ║                                                           ║
    ║     Try it yourself with: ./amaze-d -v < your_file.txt   ║
    ║                                                           ║
    ╚═══════════════════════════════════════════════════════════╝
EOF
echo -e "${RESET}\n"

echo -e "${CYAN}Available options:${RESET}"
echo -e "  ${GREEN}-v, --verbose${RESET}    Show detailed information with colors"
echo -e "  ${GREEN}-s, --stats${RESET}      Show statistics"
echo -e "  ${GREEN}-a, --animate${RESET}    Animate simulation (slower)"
echo -e "  ${GREEN}--no-color${RESET}       Disable colors"
echo -e "  ${GREEN}--no-emoji${RESET}       Disable emojis"
echo ""
