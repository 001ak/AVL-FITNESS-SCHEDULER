# Health Club Management System

## Overview

This project implements a health club management system using tree data structures (AVL tree, B-tree, or B+ tree). The system manages records of members and trainers, schedules training slots, and ensures compliance with COVID-19 norms.

## Problem Statement

The health club owner wants to store records of members, trainers, and schedule training slots. The club offers the following programs: Yoga, Cardio, Zumba, and Weight lifting. The system ensures that not more than 10 members are present in the club at any time. Each program requires a 1-hour slot, and a trainer can train only one member during this slot.

### Requirements

1. **Data Structures**: Use Trees (AVL tree, B-tree, or B+ tree) for storage.
2. **Fields**:
    - **Members**: Member-ID (4-digit randomly generated number), name, age, gender, programs enrolled, fees paid.
    - **Trainers**: Trainer-ID, name, list of programs they can train, remuneration per session.
3. **Functions**:
    - `Add_member()`
    - `Add_trainer()`
    - `Schedule_slot()`
    - `Print_hour_wise_list()`
    - `Delete_member()`
    - `Delete_trainer()`
    - `Search_member()`
    - `Search_trainer()`
    - `Print_member_list()`
    - `Print_trainer_list()`
    - `Print_sorted_remuneration_list()`
    - `Range_Search()`

### Functionalities

1. **Add_member()**
    - Input: Member details (Member-ID is randomly generated).
    - Output: Confirmation message.

2. **Add_trainer()**
    - Input: Trainer details.
    - Output: Confirmation message.

3. **Schedule_slot()**
    - Input: List of member requests (program, preferred time slot, preferred trainer), and list of available trainers.
    - Output: Schedule of assigned slots and list of non-assigned members.

4. **Print_hour_wise_list()**
    - Output: Hour/Slot-wise list of members & trainers grouped by programs.

5. **Delete_member()**
    - Input: Member-ID.
    - Output: Confirmation message.

6. **Delete_trainer()**
    - Input: Trainer-ID.
    - Output: Confirmation message.

7. **Search_member()**
    - Input: Key field and key-value.
    - Output: Member record based on key-value.

8. **Search_trainer()**
    - Input: Key field and key-value.
    - Output: Trainer record based on key-value.

9. **Print_member_list()**
    - Output: Records of all members.

10. **Print_trainer_list()**
    - Output: Records of all trainers.

11. **Print_sorted_remuneration_list()**
    - Output: Trainers sorted by remuneration (highest to lowest).

12. **Range_Search()**
    - Input: From-Member-ID, To-Member-ID.
    - Output: List of members within the ID range.

## File Structure

- `prg.c`: Contains the implementation of the health club management system.

## How to Use

1. Clone the repository.
2. Compile the `prg.c` file.
3. Run the executable to interact with the menu-driven program.

## Compilation and Execution

```sh
gcc -o health_club prg.c
./health_club
