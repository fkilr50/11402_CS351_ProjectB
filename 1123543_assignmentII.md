Name: Marvel Aiken  
Student ID: 1123543  
Course: IN321 AI-assisted Software Development  
Date: 2026/05/25

# 1. Introduction

In recent years, artificial intelligence has become more commonly used in software development. AI tools are now able to help developers generate code, explain errors, write documentation, and even suggest test cases. Because of this, software development has become faster and more convenient than before. However, even though AI can produce results very quickly, it does not always fully understand the real intention of the developer. This is why clear requirements are very important when using AI tools. Before asking AI to create or assist with software, the developer should first understand what the system needs to do, what input it should accept, what output it should produce, and what rules it must follow. Without these details, AI may generate something that looks correct on the surface, but does not actually solve the real problem.

In this assignment, three development approaches will be discussed, which are Specification-Driven Development, Behavior-Driven Development, and Test-Driven Development. SDD is useful because it focuses on writing clear specifications before development starts. BDD is useful because it explains the expected behavior of the system through real scenarios. TDD is useful because it helps developers check whether the system works correctly by designing tests before implementation. These three approaches are especially important in the AI era because they can guide AI-generated work and help developers evaluate whether the result is correct or not.

# 2. Definition of SDD

Specification-Driven Development (SDD) is a development approach where the requirements and specifications of the software are written clearly before the actual implementation begins. In this approach, the developer first focuses on understanding what the software should do, what problems it should solve, what inputs it needs, and what outputs it should produce. After the specification is clear, the development process can continue with a more stable direction.

The main purpose of SDD is to reduce confusion during development. If the specification is not clear enough, the software may still be created, but it may not match the real needs of the user. This is especially important when using AI tools because AI can generate code or explanations very quickly, but it still depends heavily on the instructions given by the user. One article about SDD in AI-assisted coding also explains that AI-generated code can suffer from ambiguity, weak context, testing gaps, and integration problems if the developer does not give a structured specification first (Punniyakotti, 2026). Because of this, the specification can be seen as the main source of truth that guides both the developer and the AI tool.

# 3. SDD: Student Grade Calculator

## Overview

The Student Grade Calculator is a simple program that calculates a student's final score and letter grade. The program will take in the scores from four different components, which are assignment, midterm exam, final exam, and project. After taking in all of the scores, the program should calculate the final weighted score and output the result to the user. The calculator should be simple to understand and use, as it only needs four score values as the input.

## Description

The Student Grade Calculator will help the user find the final grade of a student without calculating it manually. The user will input the assignment score, midterm exam score, final exam score, and project score. The program will then calculate the final score based on the weight of each component.

The supported calculation will be:

```text
Final Score = (Assignment x 0.30) + (Midterm x 0.20) + (Final Exam x 0.30) + (Project x 0.20)
```

After the final score is calculated, the program will convert the score into a letter grade. The final score should also be rounded to one decimal place so that the result is easier to read.

## Functional Requirements

After inputting all four scores, the program should output the student's final weighted score and the correct letter grade. The assignment score and final exam score will each contribute 30% to the final score, while the midterm exam and project score will each contribute 20%.

If the user inputs a score that is outside the valid range, the program should not continue the calculation. An error should be shown as a result. Problems such as scores below 0, scores above 100, missing values, or non-numeric input should be considered invalid.

## Input Requirements

The program should receive four input values:

- Assignment score
- Midterm exam score
- Final exam score
- Project score

Each input must be a number between 0 and 100. This means that values such as -10 or 120 should not be accepted by the program. The program should also reject input that is not a number.

## Output Requirements

The program should output:

- The final weighted score
- The letter grade

For example, if the student's final score is 86.5, the program should output the final score as 86.5 and the letter grade as B.

## Grade Rules

The letter grade will be decided based on the final weighted score after it is rounded to one decimal place.

- A: 90.0 to 100.0
- B: 80.0 to 89.9
- C: 70.0 to 79.9
- D: 60.0 to 69.9
- F: below 60.0

This means that if a student receives exactly 90.0, the grade should be A. If the student receives exactly 80.0, the grade should be B. If the student receives exactly 60.0, the grade should be D.

## UI Requirement

Because this is only a simple student grade calculator, a simple text-based interface will be enough. The user only needs to enter the four required scores, and the program will display the final result. There is no need for a complicated graphical interface because the main purpose of the program is only to calculate and show the final grade.

## Design

The program can be divided into several simple parts:

- Main program = controls the flow of the program.
- Input handler = receives the four scores from the user.
- Validator = checks whether the scores are valid or not.
- Grade calculator = calculates the final weighted score.
- Grade converter = converts the final score into a letter grade.
- Output display = prints out the final score and letter grade.

## Acceptance Criteria

The calculator can be considered correct if it follows the required formula, rounds the final score to one decimal place, and gives the correct letter grade according to the grade rules. The calculator should also reject invalid input before calculating the result. For example, if the user inputs 105 for one score, the program should not calculate the final grade because all scores must be between 0 and 100.

## Testing Plan

Testing will be done by checking normal cases, boundary cases, and invalid input cases. Normal cases will be used to check whether the calculator can correctly calculate a regular student's final score. Boundary cases will be used to check scores that are exactly on the grade limits, such as 90.0, 80.0, 70.0, and 60.0. Invalid input cases will be used to check whether the program can reject incorrect values, such as negative scores, scores above 100, missing values, or text input.

# 4. Definition of Behavior-Driven Development

Behavior-Driven Development, or BDD, is a development approach that focuses on the behavior of the software from the user's point of view. Instead of only thinking about how the program is built internally, BDD focuses more on what the system should do when the user interacts with it. This means that the expected behavior of the system is written in a way that can be understood by developers, users, and other people involved in the project. BDD also encourages a shared understanding between people involved in the software, and it uses natural language examples to describe behavior and expected outcomes (Wikipedia, 2026). BDD usually uses simple scenarios to describe how the software should behave in different situations. These scenarios are often written using the Given, When, Then format. "Given" describes the starting condition, "When" describes the action taken by the user or system, and "Then" describes the expected result. This format is useful because it makes the requirement easier to understand and test.

In the AI era, BDD is also useful because it gives AI tools a clearer explanation of how the system should behave. If the behavior is written only in a vague way, the AI may misunderstand the expected result. But if the behavior is written as a clear scenario, it becomes easier for the AI and the developer to know whether the generated result is correct or not.

# 5. BDD: Student Grade Calculator

In the Student Grade Calculator, BDD can be used to describe how the calculator should behave when the user inputs different scores. Instead of only describing the calculation rules, BDD explains the situation from the user's point of view. This is useful because it makes the expected result easier to understand before the actual program is created.

## Scenario 1: Student receives a B grade

**Given** the student has an assignment score of 85, a midterm score of 80, a final exam score of 90, and a project score of 80  
**When** the calculator calculates the final weighted score  
**Then** the final score should be 84.5  
**And** the letter grade should be B

## Scenario 2: Student receives an A grade

**Given** the student has an assignment score of 95, a midterm score of 90, a final exam score of 92, and a project score of 96  
**When** the calculator calculates the final weighted score  
**Then** the final score should be 93.3  
**And** the letter grade should be A

## Scenario 3: User inputs an invalid score

**Given** the user enters an assignment score of 105, a midterm score of 80, a final exam score of 75, and a project score of 85  
**When** the calculator checks the input values  
**Then** the calculator should not calculate the final score  
**And** the calculator should show an error message because all scores must be between 0 and 100

# 6. Definition of Test-Driven Development

Test-Driven Development, or TDD, is a development approach where test cases are written before the actual code is made. Instead of writing the program first and testing it later, the developer first thinks about what the program should be able to pass. This means that the requirements of the program are turned into test cases before implementation begins. Because of this, TDD helps the developer focus on the expected result and avoid writing code that does not match the requirement.

TDD is commonly explained using the Red, Green, and Refactor cycle. Red means writing a test that fails first because the feature has not been implemented yet. Green means writing the simplest code needed to pass the test. Refactor means improving the code after the test has already passed, without changing the expected behavior of the program. This idea follows the common TDD cycle, where a failing test is written first, enough code is written to pass it, and then the code is refactored before the process repeats (Wikipedia, 2026).

In the AI era, TDD is useful because AI-generated code still needs to be checked carefully. Even if AI can generate code very quickly, it may still produce wrong logic or miss some important cases. With TDD, the developer can use test cases to check whether the AI-generated result actually works correctly. This is why TDD can be used as a way to guide and verify AI-assisted software development.

# 7. TDD: Student Grade Calculator

In the Student Grade Calculator, TDD can be used by preparing the test cases before the actual program is implemented. These tests help check whether the calculator follows the correct formula, gives the correct letter grade, and rejects invalid input. Even though there is no coding requirement in this assignment, the test cases can still show what the program should be able to pass if it were created later.

## Normal Test Cases

| Test Case | Input | Expected Final Score | Expected Letter Grade |
|---|---|---:|---|
| Normal Case 1 | Assignment = 85, Midterm = 80, Final Exam = 90, Project = 80 | 84.5 | B |
| Normal Case 2 | Assignment = 95, Midterm = 90, Final Exam = 92, Project = 96 | 93.3 | A |

The purpose of the normal test cases is to check whether the calculator can correctly calculate the final score and letter grade when all of the inputs are valid and common student scores.

## Boundary Test Cases

| Test Case | Input | Expected Final Score | Expected Letter Grade |
|---|---|---:|---|
| Boundary Case 1 | Assignment = 90, Midterm = 90, Final Exam = 90, Project = 90 | 90.0 | A |
| Boundary Case 2 | Assignment = 60, Midterm = 60, Final Exam = 60, Project = 60 | 60.0 | D |

The purpose of the boundary test cases is to check whether the calculator can correctly handle scores that are exactly on the grade limits. For example, a final score of exactly 90.0 should be an A, while a final score of exactly 60.0 should still be a D and not an F.

## Invalid Input Test Cases

| Test Case | Input | Expected Result |
|---|---|---|
| Invalid Case 1 | Assignment = 105, Midterm = 80, Final Exam = 75, Project = 85 | The calculator should reject the input because 105 is above 100. |
| Invalid Case 2 | Assignment = -5, Midterm = 70, Final Exam = 80, Project = 75 | The calculator should reject the input because -5 is below 0. |

The purpose of the invalid input test cases is to check whether the calculator can prevent incorrect values from being calculated. If the input is outside the valid range of 0 to 100, the program should not continue the calculation and should show an error message instead.

# 8. Comparison of SDD, BDD, and TDD

SDD, BDD, and TDD are all useful development approaches, but they focus on different parts of the software development process. SDD focuses on writing the specifications first, BDD focuses on the expected behavior of the system, and TDD focuses on preparing test cases before implementation. Although they are different, all three approaches can help developers avoid confusion and create software that follows the original requirements.

| Approach | Main Focus | Main Question | Common Format | Usefulness in the AI Era |
|---|---|---|---|---|
| SDD | Clear software requirements and specifications | What should the system do? | Requirement list, input/output rules, functional requirements, design notes | Helps AI understand the goal and rules of the system before generating anything |
| BDD | System behavior from the user's point of view | How should the system behave in a specific situation? | Given, When, Then scenarios | Helps AI understand real user situations and expected results |
| TDD | Testing before implementation | How can we check if the system works correctly? | Test cases with input and expected output | Helps developers verify whether AI-generated code or logic is actually correct |

From this comparison, it can be seen that these three approaches support each other. SDD gives the overall plan, BDD gives examples of the expected behavior, and TDD gives test cases to check the result. In the AI era, this is important because AI tools can help generate software quickly, but the developer still needs a clear way to guide and verify the result.

# 9. Reflection

Among the three approaches, I think BDD is the easiest to understand because it explains the system through simple real-life scenarios. The Given, When, Then format makes the behavior of the program clear without needing to think too much about code or technical design. For a simple system like the Student Grade Calculator, BDD is easy to write because the situation is already familiar. A student enters scores from assignments, exams, and projects, and the calculator gives the final score and letter grade as the result. Because of this, BDD feels more natural compared to the other two approaches. It is like explaining what should happen in a normal situation.

Among the three approaches, I think TDD is the most useful when working with AI tools. This is because AI can generate code and explanations very quickly, but the result is not always guaranteed to be correct. Sometimes AI-generated work can look correct on the surface, but still have mistakes in the logic or miss some important cases. For example, the AI may calculate the weighted score correctly, but it might give the wrong letter grade at the boundary score, such as 90.0 or 60.0. TDD helps solve this problem because the developer already has test cases with expected results before the actual implementation is created. This means that the AI-generated result can be checked more clearly instead of only being trusted directly.

However, SDD and BDD are also useful in guiding AI-generated work. SDD helps the developer give clear requirements to the AI, such as the input rules, calculation formula, output format, and grade boundaries. Without these specifications, the AI may misunderstand what the system is supposed to do. BDD helps explain the expected behavior of the system through real scenarios, which makes the requirements easier to understand. TDD then works as the final checking method to see whether the generated result follows the specification and behavior correctly.

It is also important to note that these methods are not always easy to use in real projects. From the developer discussion I read, some people mentioned that TDD, BDD, and similar methods can feel like extra work when the team does not fully understand them or when the project only focuses on fast delivery. Because of this, these approaches are most useful when the developer actually believes in the method and uses it properly. Overall, I think SDD, BDD, and TDD can support each other when using AI tools in software development, but the developer still needs to review the result carefully and not blindly trust the AI.

# 10. References and AI Tool Usage

## References

- Course GitHub page. (2026). *AssignmentII: SDD, BDD, TDD Student Grade Calculator*. https://github.com/yfhuang/YZUCSE_CS351/tree/main/Assignment/AssignmentII
- Punniyakotti, S. (2026, January 20). *Specification Driven Development (SDD) - AI First Coding Practice*. Medium. https://medium.com/ai-pace/specification-driven-development-sdd-ai-first-coding-practice-e8f4cc3c2fc4
- Wikipedia contributors. (2026). *Behavior-driven development*. Wikipedia. https://en.wikipedia.org/wiki/Behavior-driven_development
- Wikipedia contributors. (2026). *Test-driven development*. Wikipedia. https://en.wikipedia.org/wiki/Test-driven_development
- Reddit users. (2025). *Why are TDD, BDD, and DDD niche methods?* Reddit. https://www.reddit.com/r/developpeurs/comments/1jj1ank/pourquoi_le_tdd_le_bdd_et_le_ddd_sont_des/?tl=en

## AI Tool Usage

I used ChatGPT as an AI assistant to help me organize the report structure, improve the clarity of my writing, and to help check whether the examples and test cases matched the Student Grade Calculator scenario. I also used it to help compare some ideas from the additional online sources with my own report and asked it to help me convert the docx report into an md file.

However, the final content was reviewed and revised by myself before submission. I made sure that the ideas, examples, and explanations matched my own understanding of the topic. The AI tool was used mainly as a support tool for brainstorming, writing improvement, and checking the report, not as a replacement for my own work.
