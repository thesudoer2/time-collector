# Time Collector

Time Collector is a command-line C++ program for calculating total time from a series of time intervals. It allows users to input intervals in flexible formats and even apply a ratio to the final result for quick time adjustments (such as overtime or percentage calculations).

## Features

- **Flexible Input Format:**
  Supports inputs like:
  - `start1 - stop1 start2 - stop2 ...`
  - `(start1 - stop1) + (start2 - stop2) + ...`
- **Interval Calculation:**
  Calculates each interval separately and sums them for the total time.
- **Ratio Adjustment:**
  After inputing time intervals, the program prompts you for ratio and you can specify ratio
  time calculation (default ratio is 1.45 but you can change it at runtime).

## Example Usage

### Input Syntax

- With spaces:
  ```
  09:00-12:00 13:00-15:30
  ```
- With parentheses and plus signs:
  ```
  (09:00-12:00) + (13:00-15:30)
  ```

### Example

**Input:**
```
08:30-12:00 13:00-17:00
```
**Output:**
```
Total time: 7 hours 30 minutes
```

**Output:**
```
Total time: 11 hours 15 minutes
```

## How It Works

1. **Input Parsing:**
   The program parses the input string, extracting each time interval.
2. **Interval Calculation:**
   Each interval (e.g., `09:00-12:00`) is calculated by finding the difference between start and stop times.
3. **Summation:**
   All calculated intervals are summed.

## Building

This project is written in C++. You can build it using g++ or any standard C++ compiler:

```sh
mkdir build
cd build
cmake ../
cmake --build . -j
```

## Usage

Run the program and input your intervals as described above:

```sh
./time_collector
```

## Notes

- Time format should be `HH:MM` (24-hour format).
- You can use spaces, plus signs, or parentheses for grouping.