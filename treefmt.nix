{ ... }:
{
  projectRootFile = "flake.nix";
  programs = {
    black.enable = true;
    clang-format.enable = true;
    nixfmt.enable = true;
  };
}
