# LSM-tree on OCSSD

This repository contains the implementation of an LSM-tree (Log-Structured Merge-tree) on FEMU-simulated OCSSD (Open-Channel Solid State Drive) using SPDK (Storage Performance Development Kit) for I/O. The LSM-tree is a widely used data structure to implement key-value stores, providing efficient I/O performance for write-heavy workloads.

## Preliminaries

Before using this implementation, please ensure that you have the following dependencies installed:

- FEMU: A fast and flexible SSD emulator for QEMU. You can find the installation instructions [here](https://github.com/ucare-uchicago/femu).
- OCSSD: Ensure that you have an OCSSD-supported SSD or a properly configured OCSSD emulator [here](https://github.com/OpenChannelSSD/liblightnvm).
- SPDK: The Storage Performance Development Kit. You can find the installation instructions [here](https://spdk.io/doc/getting_started.html).

## Install

To install and build the LSM-tree implementation, follow these steps:

1. Clone the repository:

```
git clone https://github.com/username/repository.git
```

2. Change to the repository directory:

```
cd repository
```

3. Build the project:

```
make
```

## Usage

To run the LSM-tree on FEMU-simulated OCSSD with SPDK I/O, follow these steps:

1. Start the FEMU QEMU instance with the OCSSD:

```
/path/to/femu/build/bin/qemu-system-x86_64 \
  -m 4G \
  -enable-kvm \
  -hda /path/to/your/OS-image \
  -smp 4 \
  -drive file=/path/to/your/SSD-image,if=none,id=myssd \
  -device nvme,drive=myssd,serial=myssd-0001
```

2. Run the LSM-tree application:

```
./lsm-tree
```

## Generator

This README was generated using the GPT-4 language model.

## Badge

You can show your support for this project by adding a badge to your project's README:

```
[![LSM-tree on FEMU-simulated OCSSD with SPDK I/O](https://img.shields.io/badge/LSM--tree-OCSSD--SPDK-brightgreen)](https://github.com/username/repository)
```

## Example Readmes

For more example READMEs, please check out the following repositories:

- [FEMU](https://github.com/ucare-uchicago/femu)
- [SPDK](https://github.com/spdk/spdk)

## Related Efforts

- [RocksDB](https://rocksdb.org): A persistent key-value store for fast storage environments.
- [LevelDB](https://github.com/google/leveldb): A fast key-value storage library written at Google that provides an ordered mapping from string keys to string values.

## Maintainers

- [Your Name](https://github.com/username)

## Contributing

Please read the [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to contribute to this project.

## References

- [FEMU: A Fast and Flexible SSD Emulation Framework](https://www.usenix.org/conference/atc18/presentation/ye)
- [SPDK: A High-Performance, User-Space, Poll-Mode Storage Stack](https://spdk.io)

## License

This project is licensed under the [MIT License](LICENSE).
