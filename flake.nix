{
  inputs = {
    utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, utils }: utils.lib.eachDefaultSystem (system:
    let
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShell = pkgs.mkShellNoCC {
        packages = with pkgs; [
          platformio
          doxygen
          clang-tools
          ccls
        ];
        shellHook = ''
          export PLATFORMIO_CORE_DIR=$PWD/.platformio
        '';
      };
    }
  );
}
