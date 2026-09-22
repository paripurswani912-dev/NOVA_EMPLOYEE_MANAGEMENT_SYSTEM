# NOVA EMPLOYEE MANAGEMENT SYSTEM

## Master Project Specification — Version 1

---

# 1. Project Overview

**Project Name:** NOVA Employee Management System

NOVA is a small-company employee management and HR management system implemented as a **C++ command-line application**.

The system will manage:

* Employees
* HR personnel
* Super Admin
* Attendance
* Paid leave
* Salary
* Salary raises
* Salary payments
* Performance ratings
* Promotions
* Audit trails
* Activity/notification dashboards
* User accounts
* Historical records

The system will use **file-based persistent storage**, so information remains available after the program closes.

The project will deliberately incorporate concepts from all four units of the OOP syllabus wherever they naturally fit.

---

# 2. Main System Entry

```text
========================================
       NOVA EMPLOYEE MANAGEMENT SYSTEM
========================================

1. Admin Login
2. Employee Login
0. Exit
========================================
```

The system identifies the administrator's role from the stored account.

There is no need for the user to separately select:

* Super Admin
* HR

The credentials determine the role.

---

# 3. User Roles

NOVA has three levels of users:

```text
                 SUPER ADMIN
                 /          \
                /            \
              HR          Employees
```

## 3.1 Super Admin

There is only one Super Admin.

The Super Admin has the highest authority.

The Super Admin can:

* Manage HR accounts
* Create HR accounts
* Delete HR accounts
* Manage employees
* Create employee accounts
* Delete employee accounts
* Manage employee records
* Mark employee attendance
* Mark HR attendance
* Manage salary raise requests
* Approve/reject salary raises
* Give promotions
* Change designation through promotion
* Give performance ratings to HR
* Manage salary payments
* View system activity
* View audit trails

The Super Admin can also view their own personal records where applicable.

---

# 4. HR Role

HR manages day-to-day employee-related operations.

HR can:

* Manage employee attendance
* Manage employee salary
* Request salary raises
* View employee details
* View employee records
* Give performance ratings to employees
* View their own records
* View their own attendance
* View their own salary
* View their own department/designation
* View their own performance rating
* View their own salary payment history
* View their own audit trail
* View their own activity dashboard
* View relevant activity related to their HR work

## Important HR restrictions

HR:

* Cannot create HR accounts
* Cannot create employee accounts
* Cannot delete employee accounts
* Cannot give promotions
* Cannot directly approve salary raises
* Cannot mark their own attendance
* Cannot mark another HR's attendance

HR can **request** a salary raise, but the Super Admin makes the final approval decision.

---

# 5. Employee Role

Employees have read-only access to their own information.

An employee can never access another employee's records.

Employee dashboard:

```text
========================================
          EMPLOYEE DASHBOARD
========================================

1. View Attendance
2. View Salary
3. View Department & Designation
4. View Performance Rating
5. View Salary Payment History
6. View Audit Trail
7. View Activity Dashboard

0. Logout
========================================
```

The employee cannot modify these records.

---

# 6. Employee Attendance

Attendance is managed by authorized administrators.

## Who can mark attendance?

| User        | Employee Attendance | HR Attendance | Own Attendance |
| ----------- | ------------------- | ------------- | -------------- |
| Super Admin | Yes                 | Yes           | N/A            |
| HR          | Yes                 | No            | No             |
| Employee    | No                  | No            | No             |

In the small-company model used by NOVA:

* Super Admin can mark HR attendance.
* Super Admin can mark employee attendance.
* HR can mark employee attendance.
* HR cannot mark their own attendance.
* Employees cannot mark their own attendance.

HR and employees can view their own attendance.

---

# 7. Attendance Rules

HR marks employee attendance as:

* Present
* Paid Leave
* Absent

Each employee receives a maximum of:

**2 paid leaves per month.**

If HR attempts to give a third paid leave in the same month:

```text
ERROR:
Maximum paid leave limit for this month has been reached.

The employee will be marked Absent.
```

The third leave is therefore NOT accepted as paid leave.

---

# 8. Attendance Percentage

Attendance percentage is based ONLY on Present days.

Paid leave is displayed separately.

Absence is displayed separately.

Formula:

```text
Attendance % =
Present Days / Working Days × 100
```

Example:

```text
Working Days = 22
Present = 18
Paid Leave = 2
Absent = 2

Attendance % =
18 / 22 × 100
= 81.82%
```

Paid leave is NOT counted as Present for the attendance percentage.

However:

```text
Paid Days for Salary =
Present Days + Paid Leave
```

Example:

```text
18 Present + 2 Paid Leave = 20 Paid Days
```

Therefore, paid leave contributes to salary calculation even though it does not increase the attendance percentage.

---

# 9. Salary Management

Salary management has two important concepts:

## 9.1 Salary Raise

HR does not directly change an employee's salary.

HR submits a salary raise request.

The request contains:

```text
Employee ID
Current Salary
Proposed Salary
Reason / Note
Request Date
Status
Requested By
```

Example:

```text
Employee ID: EMP102
Current Salary: ₹40,000
Proposed Salary: ₹45,000

Reason:
Consistently high performance and increased responsibilities.

Request Date:
20-09-2026

Status:
PENDING
```

---

# 10. Salary Raise Approval

The workflow is:

```text
HR
 |
 | Submit salary raise request
 ↓
PENDING REQUEST
 |
 ↓
SUPER ADMIN
 |
 +---- Approve ----> Salary Updated
 |
 +---- Reject -----> Salary Unchanged
```

The Super Admin can see how many pending requests exist.

For each request, the Super Admin can view:

* Employee
* Current salary
* Proposed salary
* Reason
* HR who submitted the request
* Request date
* Status

If approved, NOVA records:

* Approval status
* Approving Super Admin
* Approval date
* New salary

The employee's actual salary changes only after approval.

---

# 11. Salary Raise vs Promotion

These are two separate operations.

## Salary Raise

HR can:

* Request a salary raise.

Super Admin:

* Approves or rejects the request.

## Promotion

Only the Super Admin can:

* Promote an employee
* Change the employee's designation/post through promotion

HR cannot promote employees.

Therefore:

```text
Salary Raise:
HR → Request → Super Admin → Approve/Reject

Promotion:
Super Admin → Directly promotes employee
```

---

# 12. Salary Payment

NOVA will also record when an employee's salary has actually been paid/credited.

The authorized administrator can enter:

```text
Employee ID
Salary Month
Amount
Payment Date
```

Example:

```text
Employee ID: EMP102
Salary Month: September 2026
Amount: ₹45,000
Payment Date: 30-09-2026
```

The payment should then appear in:

### Employee Salary Payment History

```text
Month       Amount       Status       Payment Date
September   ₹45,000      Paid         30-09-2026
```

The payment action should also generate an activity notification and audit entry.

---

# 13. Salary History

Salary changes should not simply overwrite the old information.

NOVA should maintain historical salary information.

Example:

```text
Date        Salary       Reason
01-Jul      ₹40,000      Initial salary
21-Sep      ₹45,000      Approved salary raise
```

For salary raises, the reason/note should be preserved.

The approving Super Admin should also be recorded.

---

# 14. Performance Ratings

Performance ratings are given hierarchically.

```text
SUPER ADMIN
      |
      | rates
      ↓
     HR
      |
      | rates
      ↓
  EMPLOYEE
```

Therefore:

* Super Admin gives performance ratings to HR.
* HR gives performance ratings to employees.
* Employees can only view their own ratings.
* HR can view their own rating given by Super Admin.
* Super Admin can view ratings across the system as permitted.

---

# 15. Monthly Performance Evaluation

Performance rating is not a single permanent value.

NOVA maintains a **monthly performance history**.

Example:

```text
Employee: EMP102

Month       Rating       Given By
June        4/5          HR001
July        3/5          HR001
August      5/5          HR001
September   4/5          HR001
```

A rating record contains:

```text
Employee
Month
Rating
Remarks
Given By
Evaluation Date
```

Example:

```text
Employee: EMP102
Month: June 2026
Rating: 4/5

Remarks:
Good performance and consistent attendance.

Evaluation Date:
30-06-2026
```

---

# 16. Time-Based Performance System

NOVA should use the current system date to determine whether a monthly performance evaluation has been completed.

At the end of a month, the system can determine:

```text
September Performance Ratings

EMP101 → Rated
EMP102 → Not Rated
EMP103 → Rated
```

When an authorized user logs in, NOVA can display a reminder such as:

```text
⚠ MONTHLY PERFORMANCE TASK

September performance ratings are pending.

Employees pending rating: 1

1. Give Ratings
2. View Pending Employees
3. Later
```

The program does NOT need to run continuously waiting for midnight.

Instead, it checks the current date when the program is running.

---

# 17. Activity / Notification Dashboard

NOVA will have an **Activity Dashboard** for users.

This is different from the Audit Trail.

## Activity Dashboard

Purpose:

> Show the user important recent events that they should know about.

## Audit Trail

Purpose:

> Record what action happened, to whom, when, and who performed it.

---

# 18. Employee Activity Dashboard

Employees can receive events such as:

```text
20-Sep-2026
✓ Attendance marked Present

18-Sep-2026
✓ Paid Leave recorded

30-Sep-2026
✓ Salary ₹40,000 credited

21-Sep-2026
✓ Your salary was increased
  from ₹40,000 → ₹45,000
```

Employees do not manually create these notifications.

The system generates them when relevant actions occur.

---

# 19. HR Activity Dashboard

HR can see personal events and relevant work events.

Example:

```text
20-Sep-2026
✓ Your attendance marked Present

20-Sep-2026
✓ Leave recorded for you

20-Sep-2026
✓ Salary raise request submitted
  for EMP102

21-Sep-2026
✓ Salary raise request for EMP102
  was APPROVED by Super Admin
```

HR therefore gets both:

* Personal employment activity
* Relevant HR-operation activity

---

# 20. Super Admin Activity Dashboard

Super Admin has broader system-level activity.

Example:

```text
20-Sep-2026
• HR001 submitted salary raise request
  for EMP102

20-Sep-2026
• Attendance marked for EMP102

21-Sep-2026
• Salary raise for EMP102 APPROVED

30-Sep-2026
• Salary payment recorded for EMP102
```

---

# 21. Audit Trail

The Audit Trail automatically records important system actions.

Users do NOT manually write audit entries.

Example:

```text
Date         Actor       Action
01-Sep       SA001       Employee created
03-Sep       HR002       Attendance marked
05-Sep       HR002       Rating updated
15-Sep       HR002       Attendance corrected
20-Sep       HR002       Salary raise requested
21-Sep       SA001       Salary raise approved
30-Sep       SA001       Salary payment recorded
```

An audit record should ideally identify:

* Date/time
* Actor
* Action
* Affected employee/person
* Relevant details

Employees can view only their own relevant audit trail.

HR can view their own audit trail and appropriate employee-related activity.

Super Admin has broader audit visibility.

---

# 22. HR — Manage HR Information

Super Admin's HR management section will contain:

```text
MANAGE HR

1. Add HR
2. View HR
3. Edit HR
4. Delete HR
5. View HR Records
6. Add / Update HR Performance Rating
7. View HR Audit Trail
8. Back
```

Super Admin creates HR accounts, including:

* HR ID
* Name
* Password
* Other required employment information

---

# 23. Employee Account Creation

Only Super Admin creates employee accounts.

When creating an employee, the Super Admin can establish:

* Employee ID
* Name
* Password
* Department
* Designation
* Initial salary
* Other required employee information

HR does not create employee accounts.

---

# 24. Authentication

Employee login:

```text
Employee ID / Username
Password
```

Admin login:

```text
Admin ID
Password
```

The stored account determines whether the administrator is:

```text
Super Admin
```

or

```text
HR
```

Wrong credentials should produce an error and allow:

* Retry
* Back

Credentials should be stored persistently rather than hard-coded into `main.cpp`.

---

# 25. Navigation Rules

NOVA should always provide a way to move backward or exit.

Suggested convention:

```text
0. Back
```

inside submenus.

```text
0. Logout
```

inside dashboards.

```text
0. Exit
```

on the main screen.

---

# 26. Dates and Time — Core System Requirement

Date/time is an important system-wide concept.

It will be used for:

* Attendance dates
* Leave dates
* Monthly paid-leave calculations
* Salary payment dates
* Salary months
* Salary raise request dates
* Salary raise approval dates
* Performance evaluation dates
* Performance evaluation month
* Promotion dates
* Audit trail timestamps
* Activity timestamps
* Employee creation/joining dates where applicable

NOVA should eventually have a **consistent date/time mechanism** rather than implementing dates differently in every module.

---

# 27. Data Persistence

NOVA will use files so that data survives after the program closes.

Possible data categories include:

```text
Users / Accounts
Employees
Attendance
Leave
Salary
Salary Raise Requests
Salary Payments
Performance Ratings
Promotions
Audit Trail
Activity / Notifications
```

The exact file structure should be decided during the data-design phase.

The project can use:

* File streams
* Binary files
* Appropriate file modes
* Random access where it makes sense

These will also help demonstrate Unit IV concepts.

---

# 28. Important Design Principle

One action should update all relevant system records automatically.

For example:

```text
Super Admin approves salary raise
              ↓
      Employee salary updated
              ↓
      Salary history updated
              ↓
      Activity generated
              ↓
      Audit entry generated
```

Similarly:

```text
HR marks attendance
        ↓
Attendance record updated
        ↓
Activity generated
        ↓
Audit entry generated
```

This prevents the user from entering the same information repeatedly.

---

# 29. OOP Direction

The project must eventually demonstrate the concepts taught across all four units.

Potentially relevant concepts include:

### Unit I

* Classes/objects
* Functions
* Function overloading
* Default arguments
* Inline functions
* Friend functions
* References
* Typecasting
* Control structures
* Strings

### Unit II

* Access specifiers
* Constructors
* Destructors
* Static members
* Arrays/strings
* Operator overloading
* Friend operator functions
* Type conversion

### Unit III

* Inheritance
* Protected members
* Function overriding
* Multiple/multilevel/hierarchical/hybrid inheritance where genuinely appropriate
* Virtual functions
* Pure virtual functions
* Polymorphism
* `this`
* Pointers and objects

### Unit IV

* File streams
* Binary files
* File modes
* Random access
* UML
* Class diagrams
* State diagrams
* Use-case diagrams
* Activity diagrams
* Interaction diagrams

**Important:** We should not force every concept into the system artificially. Each concept should have a defensible reason for existing in NOVA.

---

# 30. Current Development Status

## CONFIRMED

* Project name: NOVA Employee Management System
* CLI-based C++ system
* Three roles: Super Admin, HR, Employee
* Employee has six core record-viewing options
* Employee activity dashboard
* HR activity dashboard
* Super Admin activity dashboard
* Attendance rules
* Two paid leaves per month
* Attendance percentage based only on Present
* Paid leave separately displayed
* Absent separately displayed
* Paid leave + Present used for salary calculation
* HR manages employee attendance
* Super Admin can mark HR attendance
* Super Admin can mark employee attendance
* Employees cannot mark attendance
* HR cannot mark own attendance
* Salary raise request system
* HR can request raises
* Super Admin approves/rejects raises
* Reason/note required for raise requests
* Request date recorded
* Approval date recorded
* Salary history maintained
* Salary payment recording
* Payment date recorded
* Super Admin can record salary payment
* Promotion restricted to Super Admin
* Performance rating hierarchy
* Monthly performance ratings
* Performance history
* Date/time used throughout the system
* Automatic audit trail
* Activity/notification system
* File-based persistent storage
* Back/logout/exit navigation

---

# 31. NOT YET FINALIZED

Keep this section specifically for decisions that still need to be made.

Examples:

* Exact employee personal-information fields
* Exact HR personal-information fields
* Exact department list
* Exact designation list
* Exact performance-rating scale
* Exact promotion workflow/details
* Exact salary-payment authority/menu structure
* Exact salary calculation formula
* Exact file format
* Exact class hierarchy
* Exact use of every syllabus OOP concept
* Exact UML diagrams
* Exact company data/sample records

Do NOT silently make these decisions while coding.

---

# 32. Recommended Build Order

Do not start by writing the entire program.

Build NOVA in this order:

### Phase 1 — Documentation

Finish:

```text
Project Overview
↓
Roles & Permissions
↓
Feature Rules
↓
Data Requirements
```

This document is the current foundation.

---

### Phase 2 — Data Design

Before classes, decide what information each record needs.

For example:

```text
Employee
----------------
Employee ID
Name
Password
Department
Designation
Salary
...
```

Then separately:

```text
Attendance Record
-----------------
Employee ID
Date
Status
...
```

And:

```text
Salary Raise Request
--------------------
Request ID
Employee ID
Current Salary
Proposed Salary
Reason
Requested By
Request Date
Status
Approved By
Approval Date
...
```

We will design these **one at a time**.

---

### Phase 3 — Class Design

Only after the data is clear, decide:

```text
What classes do we actually need?
What inherits from what?
Which members are private/protected/public?
Where do constructors/destructors belong?
Where does polymorphism genuinely help?
Where can operator overloading be meaningful?
```

This is where we deliberately map the syllabus to the project.

---

### Phase 4 — File Design

Decide:

```text
What gets stored?
Which file stores it?
Binary or text?
How is a record searched?
How is it updated?
How is it deleted?
```

---

### Phase 5 — UML

Create:

* Use-case diagram
* Class diagram
* Activity diagrams
* State diagrams
* Interaction/sequence-style diagrams as required

The diagrams should come from the actual design, **not be invented separately for the report**.

---

### Phase 6 — Coding

Then build incrementally:

```text
Login
 ↓
Role identification
 ↓
Dashboards
 ↓
Employee records
 ↓
Attendance
 ↓
Salary
 ↓
Salary requests
 ↓
Payments
 ↓
Performance
 ↓
Promotion
 ↓
Audit trail
 ↓
Activity dashboard
 ↓
Final integration
```

After every module:

**build → test → fix → move on.**

Do NOT write 5,000 lines and pray. 😭

---

# 33. What You Should Do Right Now

Your immediate task is **NOT coding**.

Create the project folder:

```text
NOVA_EMPLOYEE_MANAGEMENT_SYSTEM
```

Inside it create:

```text
docs
src
data
```

Then create:

```text
docs/01_Project_Overview.md
docs/02_Features_and_Rules.md
```

Put this master specification into your documentation.

Then our **next actual design session should be DATA DESIGN**.

We'll take one entity at a time:

```text
Employee
↓
HR
↓
Super Admin
↓
Attendance
↓
Leave
↓
Salary
↓
Salary Raise Request
↓
Salary Payment
↓
Performance Rating
↓
Promotion
↓
Audit Trail
↓
Activity/Notification
```

For each one, **you tell me what information you think it needs**, and I'll challenge it if something is missing or redundant.

Only after that will we touch the C++ classes.

That way, even if you inevitably come back tomorrow and say, *"WAIT, I HAVE ANOTHER FEATURE"* 😂, we can add it to the specification without destroying the whole codebase.
