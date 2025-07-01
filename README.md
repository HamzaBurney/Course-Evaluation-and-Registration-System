# Course Evaluation and Registration System

This project is a C++ based application that simulates a university-level Course Registration and Evaluation System. It handles student registrations, teacher assignments, and course-related evaluations such as quizzes, exams, and final marks.

## 📦 Project Structure

```
├── Course.h                  # Course class definition
├── Date.h                    # Date management 
├── Display.h                 # Handles output displays
├── main.cpp                  # Entry point of the application
├── Student.h / Teacher.h     # Definitions for Student and Teacher entities
├── Course Registration Data - Sheet1.csv
├── MarkSheet.csv             # Contains student marks
├── Answers.csv               # Contains quiz/exam answers
├── Pending Quiz.csv          # Students with pending quizzes
├── Examination System for Course Evaluation.pdf
├── Class Design.pdf          # System design and class relationship
```

## 🚀 Features

- Load and parse student-course registration data from CSV
- Map courses to teachers and students
- Process quizzes and marks from separate CSVs
- Evaluate students based on uploaded answers and quiz files
- Display results and summaries through a command-line interface

## 🛠 Requirements

- C++ Compiler (C++11 or later)
- A terminal or IDE to compile and run the program
- CSV files placed in the same directory as the executable

## 🧪 How to Run

1. Make sure all `.cpp`, `.h`, and `.csv` files are in the same directory.
2. Compile the project:
   ```bash
   g++ main.cpp -o CourseSystem
   ```
3. Run the executable:
   ```bash
   ./CourseSystem
   ```

## 📁 Data Files

The application depends on these CSV files:
- `Course Registration Data - Sheet1.csv`: student-course mapping
- `MarkSheet.csv`: contains student marks
- `Answers.csv`: expected correct answers
- `Pending Quiz.csv`: tracks incomplete assessments

## 📖 Documentation

- `Examination System for Course Evaluation.pdf`: System usage and overview
- `Class Design.pdf`: Visual structure and relationships among classes

## 📜 License

This project is provided for educational purposes and is free to use, modify, and distribute.

## ✍️ Author

Developed by [Hamza Burney]
