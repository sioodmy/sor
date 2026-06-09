{
  description = "sor";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    treefmt-nix.url = "github:numtide/treefmt-nix";

  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      treefmt-nix,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };

        treefmtEval = treefmt-nix.lib.evalModule pkgs ./treefmt.nix;

        pythonEnv = pkgs.python3.withPackages (
          ps: with ps; [
            streamlit
            pandas
          ]
        );

        simulation = pkgs.stdenv.mkDerivation {
          pname = "sor-sims4";
          version = "1.0.0";

          src = ./.;

          buildInputs = [ ];
          nativeBuildInputs = [ pkgs.gnumake ];

          buildPhase = ''
            make directories
            make bin/symulacja
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp bin/symulacja $out/bin/symulacja

            mkdir -p $out/config
            cp config/config.ini $out/config/config.ini
          '';
        };

        dashboard = pkgs.writeShellApplication {
          name = "sor-dashboard";
          runtimeInputs = [ pythonEnv ];
          text = ''
            export STREAMLIT_SERVER_FILE_WATCHER_TYPE=none
          '';
        };

        docs = pkgs.stdenv.mkDerivation {
          pname = "sor-docs";
          version = "1.0.0";
          src = ./.;

          nativeBuildInputs = [ pkgs.doxygen ];

          buildPhase = ''
            doxygen Doxyfile
          '';

          installPhase = ''
            mkdir -p $out
            cp -r docs_out/html/* $out/
          '';
        };

      in
      {
        formatter = treefmtEval.config.build.wrapper;

        checks = {
          formatting = treefmtEval.config.build.check self;
        };

        packages = {
          default = simulation;
          simulation = simulation;
          dashboard = dashboard;
          docs = docs;
        };

        devShells.default = pkgs.mkShell {
          packages = [
            pkgs.gnumake
            pkgs.gcc
            pkgs.valgrind
            pkgs.doxygen
            pkgs.gtest
            pythonEnv
          ];

        };
      }
    );
}
