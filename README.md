# Patient Records Manager

Command-line application in C to manage patients and their blood pressure and body measurements records. Patients and records are kept in linked lists in memory and persisted to text files.

University project for the *Princípios de Programação Procedimental* (Procedural Programming Principles) course, Computer Engineering (LEI), University of Coimbra, 2024.

## Features

- Register a new patient (name, date of birth, citizen card, phone number and email), with input validation
- Remove a patient
- Add a record to a patient: date, maximum and minimum blood pressure, weight and height
- List all patients, or show all the information of one patient
- List the patients with a maximum blood pressure above a given value
- Sort the patient list alphabetically or by ID
- Load and save patients and records from text files

## Project Structure

| File | Contents |
|---|---|
| `main.c` | Interactive menu and program flow |
| `Doente.c/.h` | Patient structure, creation and validation (phone, email, citizen card) |
| `ListaDoentes.c/.h` | Linked list of patients: insertion, removal, sorting, reading and writing |
| `Registo.c/.h` | Record structure (blood pressure, weight, height) |
| `ListaRegistos.c/.h` | Linked list of records |
| `Data.c/.h` | Date structure and helpers |

## Tech Stack

C (C17) · CMake

## Getting Started

### Prerequisites

A C compiler (GCC or Clang) and, optionally, CMake 3.27 or later.

### Installation

```bash
gcc -o patient-records *.c
```

or, with CMake:

```bash
cmake -B build
cmake --build build
```

### Usage

```bash
./patient-records
```

The program reads `Doentes.txt` and `Registos.txt` from the current directory. If they do not exist it starts with an empty list and creates them when you exit. These files are not included in the repository.

## Authors

Simão Carvalho · University of Coimbra · Computer Engineering · 2024
