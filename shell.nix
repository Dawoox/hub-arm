{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    packages = with pkgs; [
        platformio
        platformio-core
        gcc
    ];
}
