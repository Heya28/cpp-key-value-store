# cpp-key-value-store

> A high-performance, concurrent K-V store built from scratch in C++ to handle networked requests.

This project is a complete, multi-threaded, networked database server built from the ground up to understand the core principles of high-performance systems.

## 📍 Current Status: Step 1 (Core Engine)

The project is currently a local-only program that runs in the terminal. It uses a `std::unordered_map` for in-memory storage and parses user input from `std::cin`.

## Features
* `SET key value`: Stores a string value.
* `GET key`: Retrieves a stored value.
* `DEL key`: Deletes a value.
* `EXIT`: Quits the program.

## 🛠 How to Compile and Run (Step 1)

```bash
# Compile the code
g++ main.cpp -o my_store -std=c++17

# Run the program
./my_store
```

Example Usage:
```
> SET name Hiya
OK
> GET name
Value is name
> EXIT
Goodbye!
```

## 🗺️ Project Roadmap
- [x] Step 1: Core Engine (A local-only terminal app)
- [ ] Step 2: Network Layer (Add a TCP server with Boost Asio)
- [ ] Step 3: Concurrency (Handle multiple clients at once with multi-threading)
- [ ] Step 4: Persistence (Save data to a file so it's not lost on restart)