.if "${OPSYS}" == "DragonFly"
BOOTSTRAP_RUST=		1.32.0
BOOTSTRAP_CARGO=	0.33.0
DF_INDEX+=		2 3 4
COMPEXT=		zst
.elif "${OPSYS}" == "FreeBSD"
BOOTSTRAP_RUST=		1.32.0
BOOTSTRAP_CARGO=	0.33.0
DF_INDEX+=		5 6 7
COMPEXT=		gz
.elif "${OPSYS}" == "Linux"
BOOTSTRAP_RUST=		1.32.0
BOOTSTRAP_CARGO=	0.33.0
DF_INDEX+=		8 9 10
COMPEXT=		gz
SFX=			${ARCH_STANDARD}-unknown-linux-gnu
.endif
SFX?=			${ARCH_STANDARD}-unknown-${OPSYS:tl}
SRC_RUSTC?=		rustc-${BOOTSTRAP_RUST}-${SFX}
SRC_RUSTSTD?=		rust-std-${BOOTSTRAP_RUST}-${SFX}
SRC_CARGO?=		cargo-${BOOTSTRAP_CARGO}-${SFX}

# Manifest files
RUST_MANIFESTS= \
	lib/rustlib/manifest-cargo \
	lib/rustlib/manifest-clippy-preview \
	lib/rustlib/manifest-miri-preview \
	lib/rustlib/manifest-rls-preview \
	lib/rustlib/manifest-rustc \
	lib/rustlib/manifest-rustfmt-preview \
	lib/rustlib/manifest-rust-analysis-${SFX} \
	lib/rustlib/manifest-rust-std-${SFX} \
	lib/rustlib/manifest-rust-src \
	lib/rustlib/manifest-rust-docs
