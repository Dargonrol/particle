{
  description = "Basic particle sim in raylib";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; };
    in
    {
       devShells.${system}.default = pkgs.mkShell {
         buildInputs = with pkgs; [
           cmake
           gcc
           pkg-config
           raylib
           clang-tools
           glm
         ];

         shellHook = ''
           echo "raylib dev environment loaded!"
           '';
       };
    };
}
