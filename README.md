# xv6-superpages

This is a modified version of MIT's xv6 operating system that adds support for **2MB superpages** (large pages) using multi-level page table mappings.

## 🧠 Why Superpages?

Superpages reduce TLB pressure and improve memory mapping efficiency by mapping larger contiguous memory regions using higher-level page table entries (level-1 instead of level-2).

---

## 🔧 Key Features

- ✅ `kalloc_super()` — allocates 2MB-aligned physical memory
- ✅ `mappages_large()` — maps virtual to physical addresses using level-1 PTEs
- ✅ Modified `uvmalloc()` — to use superpages when `va` and `pa` are 2MB aligned
- ✅ Test program `supertest` verifies mapping + access

---

## 🧪 How to Test

```bash
make qemu

in xv6-shell
$ supertest
