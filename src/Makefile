# Tag on this commit
TAG := $(shell git describe --tags --exact-match)
# Commit hash from git
COMMIT := $(shell git rev-parse --short HEAD)
VERSION := $(if $(TAG),\\\"$(TAG)\\\",\\\"$(COMMIT)\\\")

.PHONY: sync

sync:
	@echo Synchronizing GIT...
	# TODO: reject if repo is not clean
	git submodule update --init --recursive
	git submodule sync --recursive
	git submodule update --init --recursive

