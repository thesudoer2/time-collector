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
  Optionally apply a ratio (e.g., 1.5 for overtime) to the total calculated time.

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
- With a ratio:
  ```
  (09:00-12:00) + (13:00-15:30) * 1.25
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

**Input with ratio:**
```
(08:30-12:00)+(13:00-17:00) * 1.5
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
4. **Ratio (Optional):**
   If a ratio is specified (e.g., `* 1.25`), the total time is multiplied accordingly before displaying.

## Building

This project is written in C++. You can build it using g++ or any standard C++ compiler:

```sh
g++ -o time_collector main.cpp
```

Replace `main.cpp` with your main source file if the name differs.

## Usage

Run the program and input your intervals as described above:

```sh
./time_collector
```

Then enter your time intervals when prompted.

## Notes

- Time format should be `HH:MM` (24-hour format).
- You can use spaces, plus signs, or parentheses for grouping.
- Ratio is optional and should follow a `*` sign.