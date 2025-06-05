#!/bin/bash

# Get the absolute path to your script’s directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BIN_PATH="$SCRIPT_DIR/bin"

# Determine the shell config file
if [ -n "$ZSH_VERSION" ]; then
    SHELL_RC="$HOME/.zshrc"
elif [ -n "$BASH_VERSION" ]; then
    SHELL_RC="$HOME/.bashrc"
else
    echo "Unsupported shell. Please manually add the following to your shell config:"
    echo "export PATH=\"$BIN_PATH:\$PATH\""
    exit 1
fi

# Check if PATH already includes your bin
if grep -Fq "$BIN_PATH" "$SHELL_RC"; then
    echo "PATH already updated in $SHELL_RC"
else
    echo "Updating PATH in $SHELL_RC"
    echo "" >> "$SHELL_RC"
    echo "# Added by your-tool setup script" >> "$SHELL_RC"
    echo "export PATH=\"$BIN_PATH:\$PATH\"" >> "$SHELL_RC"
    echo "Done. Please restart your terminal or run: source $SHELL_RC"
fi  