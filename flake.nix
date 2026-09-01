{
  description = "Basic particle sim in raylib";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      
      pkgs = import nixpkgs { inherit system; };

      pkgsWin = import nixpkgs {
        inherit system;
        crossSystem = {
          config = "x86_64-w64-mingw32";
        };
      };
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          nix
          cmake
          gcc
          pkg-config
          raylib
          clang-tools
          glm
          pkgsCross.mingwW64.stdenv.cc
        ];

        shellHook = ''
          echo "Raylib Dev-Environment geladen!"
        '';
      };

      packages.${system} = {
        default = pkgs.stdenv.mkDerivation {
          pname = "particle";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = with pkgs; [ cmake pkg-config patchelf ];
          buildInputs = with pkgs; [ raylib glm libGL libx11 libxcursor libxrandr libxinerama libxi ];

          cmakeFlags = [ "-DCMAKE_BUILD_TYPE=Release" ];

          installPhase = ''
            mkdir -p $out/bin
            cp particle $out/bin/
            patchelf --set-interpreter /lib64/ld-linux-x86-64.so.2 $out/bin/particle
          '';
        };

        windows = pkgsWin.stdenv.mkDerivation {
          pname = "particle-win";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = [ pkgsWin.cmake pkgsWin.pkg-config ];
          buildInputs = [ 
            pkgsWin.raylib 
            pkgs.glm 
          ];

          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Release"
          ];

          installPhase = ''
            mkdir -p $out/bin
            cp particle.exe $out/bin/
          '';
        };
      };
    };
}
