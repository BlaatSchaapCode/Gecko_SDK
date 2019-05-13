# Change Log

All notable changes to the bootloader will be documented in this file. The
version number given in the Change Log is on the format `major`.`minor`.`patch`.

## 1.1.0 - 2017-06-09

### Added
 - The `bootloader_verifyApplication` function now supports verifying all
   applications. If secure boot is enforced, the function will only return
   `true` if the cryptographic signature of the application is valid. Else, the
   application is verified according to the signature type present in the
   application ApplicationProperties_t structure.
 - The SPI flash storage plugin now supports graphical configuration of SPI
   flash write protect and hold pins. Configuring these pins is required for the
   bootloader to successfully communicate with the stacked flash in the
   EFR32MG1[BP][67]32 SiPs.

### Changed
 - The internal flash write routine `flash_writeBuffer` now returns `true`
   if given a zero-length buffer to write. This improves the backwards
   compatibility of the behavior of the bootloader interface for internal
   storage bootloaders.
 - The added capability of `bootloader_verifyApplication` means that it will now
   return `true` instead of `false` when verifying an unsigned application when
   secure boot is _not_ enabled.

### Fixed
 - The Bluetooth in-place OTA bootloader sample configuration was erroneously
   not visible for EFR32MG1 in Simplicity Studio
 - The image parser for legacy EBL files would silently fail to completely apply
   upgrade images containing zero-length ERASEPROG tags, which Simplicity
   Commander sometimes could output (sequences of "FD03000400000000" near the end of
   the EBL file). If zero-length ERASEPROG tags were present, data would not be
   flashed to the word starting at address 0x8004.
 - The image parser for legacy EBL files would fail to indicate that the image
   contained an application upgrade, causing the storage plugin to abort
   the upgrade process, even though the image was valid.

## 1.0.0 - 2017-03-10
### Added
 - Initial release of Gecko Bootloader

## Change Type Descriptions
The following change types are used in this document to describe changes
### Added
- New features added to this release
### Changed
- Changes in existing functionality
### Deprecated
- Functionality that has been deprecated, and may be removed in a future release
### Removed
- Functionality that was removed in this release
### Fixed
- Bugs that were fixed in this release
### Security
- Security critical changes and fixes that should be highlighted in this release
