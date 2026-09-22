# NOVA Employee Management System — Data Design

## 1. Overview

The NOVA Employee Management System uses separate data entities for employee information, attendance, salary management, performance, promotions, and system tracking.

The system is designed so that:

* Employee information stores the employee's current details.
* Historical records preserve important changes over time.
* Actions performed by HR and Super Admin are recorded automatically.
* Calculated values such as age and attendance percentage are derived when required instead of being permanently stored.

---

# 2. People / Account Entities

## 2.1 Employee

An Employee represents a regular employee of the organization.

### Fields

| Field           | Description                                   |
| --------------- | --------------------------------------------- |
| Employee ID     | Unique employee identifier and login username |
| Password        | Employee login password                       |
| Name            | Full name of the employee                     |
| Date of Birth   | Used to calculate current age                 |
| Email           | Employee email address                        |
| Phone           | Employee contact number                       |
| Address         | Employee residential/contact address          |
| Date of Joining | Date the employee joined the organization     |
| Department      | Employee's department                         |
| Designation     | Employee's current designation                |
| Salary          | Employee's current salary                     |
| Employee Status | Active / Inactive                             |

### Derived Data

**Age** is calculated from Date of Birth and the current system date. It is not stored separately.

### Status

An employee can be:

* Active
* Inactive

Inactive employees are retained in the system so that their historical records are not lost.

---

## 2.2 HR

HR is a specialized type of Employee.

HR inherits the common employee information and has additional permissions for managing employee-related operations.

### Relationship

```text
Employee
    ↑
    |
   HR
```

### HR Responsibilities

* Manage employee attendance
* View employee records
* Submit salary raise requests
* Give employee performance ratings
* View own HR-related records

HR cannot:

* Create or delete HR accounts
* Create or delete employee accounts
* Approve salary raises
* Promote employees
* Mark their own attendance

---

## 2.3 Super Admin

Super Admin is a system-level account and is **not treated as an employee**.

There is only one Super Admin.

### Fields

| Field          | Description                   |
| -------------- | ----------------------------- |
| Super Admin ID | Unique Super Admin identifier |
| Password       | Login password                |
| Name           | Super Admin name              |

The Super Admin does not have employee-related records such as salary, department, designation, or attendance.

### Super Admin Responsibilities

* Manage HR accounts
* Manage employee accounts
* Manage employee records
* Mark employee attendance
* Mark HR attendance
* Approve/reject salary raise requests
* Promote employees
* Record salary payments
* Give HR performance ratings
* View broader system activity and audit information

---

# 3. Attendance

Attendance stores the daily attendance record of an employee.

### Fields

| Field             | Description                                 |
| ----------------- | ------------------------------------------- |
| Employee ID       | Employee whose attendance is being recorded |
| Date              | Date of attendance                          |
| Attendance Status | Present / Paid Leave / Absent               |
| Marked By         | HR ID or Super Admin ID                     |

### Attendance Rules

* HR can mark employee attendance.
* Super Admin can mark employee attendance.
* Super Admin can mark HR attendance.
* HR cannot mark their own attendance.
* Employees cannot mark their own attendance.
* An employee can have a maximum of 2 paid leaves per month.
* If a third paid leave is attempted in the same month, the system rejects the paid leave and records the day as Absent.

### Calculated Attendance Information

The following values are calculated from daily attendance records:

* Total Working Days
* Total Present
* Total Paid Leave
* Total Absent
* Attendance Percentage

### Attendance Percentage

```text
Attendance Percentage =
(Total Present / Total Working Days) × 100
```

Paid Leave is shown separately and is not counted as Present.

---

# 4. Salary

The employee's **current salary** is stored directly in the Employee record.

```text
Employee
└── Current Salary
```

Salary changes are handled through Salary History and Salary Raise Requests.

---

# 5. Salary History

Salary History stores previous salary changes so that the system does not lose historical salary information.

### Fields

| Field           | Description                             |
| --------------- | --------------------------------------- |
| Employee ID     | Employee whose salary changed           |
| Previous Salary | Salary before the change                |
| New Salary      | Salary after the change                 |
| Effective Date  | Date the new salary became effective    |
| Reason          | Reason for the salary change            |
| Changed By      | Person who authorized the salary change |

### Example

```text
Employee ID: E101
Previous Salary: ₹30,000
New Salary: ₹35,000
Effective Date: June 2026
Reason: Performance
Changed By: SA001
```

The Employee record always contains the current salary, while Salary History preserves previous changes.

---

# 6. Salary Raise Request

HR cannot directly change an employee's salary for a raise.

Instead, HR submits a salary raise request to the Super Admin.

### Fields

| Field                      | Description                                      |
| -------------------------- | ------------------------------------------------ |
| Employee ID                | Employee requesting/being considered for a raise |
| Current Salary             | Employee's salary when request is created        |
| Proposed Salary            | Salary proposed by HR                            |
| Reason                     | Reason for requesting the raise                  |
| Monthly Performance Rating | Relevant monthly performance evaluation          |
| Request Date               | Date the request was submitted                   |
| Requested By               | HR ID                                            |
| Status                     | Pending / Approved / Rejected                    |
| Decision Date              | Date Super Admin makes the decision              |
| Decided By                 | Super Admin ID                                   |

### Workflow

```text
HR submits request
        ↓
Status = Pending
        ↓
Super Admin reviews request
        ↓
   ┌────┴────┐
   ↓         ↓
Approved   Rejected
   ↓
Current Salary Updated
   ↓
Salary History Created
   ↓
Audit + Activity Generated
```

If the request is rejected, the employee's current salary remains unchanged.

---

# 7. Performance

Performance stores monthly performance ratings.

There is **one performance rating per person per month**.

### Fields

| Field            | Description                         |
| ---------------- | ----------------------------------- |
| Person ID        | Employee or HR being evaluated      |
| Evaluation Month | Month for which the rating is given |
| Rating           | Rating from 1 to 5                  |
| Remarks / Reason | Short explanation of the rating     |
| Given By         | HR ID or Super Admin ID             |
| Evaluation Date  | Date on which the rating was given  |

### Performance Hierarchy

```text
Super Admin → rates HR
HR          → rates Employees
Employee    → views own rating
HR          → views own rating given by Super Admin
```

### Example

```text
Person ID: E101
Evaluation Month: September 2026
Rating: 4/5
Remarks: Consistently completed assigned tasks on time.
Given By: HR002
Evaluation Date: 30-Sep-2026
```

The system should prevent more than one performance rating from being recorded for the same person and month.

---

# 8. Salary Payment History

Salary Payment History records actual salary payments made to employees.

The Super Admin can mark an employee's salary as paid when the salary has actually been transferred/paid.

### Fields

| Field          | Description                              |
| -------------- | ---------------------------------------- |
| Employee ID    | Employee whose salary was paid           |
| Salary Month   | Month for which the salary is being paid |
| Amount         | Amount paid                              |
| Payment Status | Paid / Not Paid                          |
| Payment Date   | Date on which salary was paid            |
| Recorded By    | Super Admin ID                           |

### Main Operation

The Super Admin can use:

```text
Mark Salary as Paid
```

The system can display:

```text
Employee: E101
Salary Month: September 2026
Amount: ₹35,000

Was the salary paid?
1. Yes
2. No
```

When the payment is confirmed, the payment date and payment information are recorded.

---

# 9. Promotion

Only the Super Admin can promote an employee.

A promotion can change both the employee's designation and salary.

### Fields

| Field                | Description                  |
| -------------------- | ---------------------------- |
| Employee ID          | Employee being promoted      |
| Previous Designation | Designation before promotion |
| New Designation      | Designation after promotion  |
| Previous Salary      | Salary before promotion      |
| New Salary           | Salary after promotion       |
| Promotion Date       | Date of promotion            |
| Promoted By          | Super Admin ID               |

### Promotion Workflow

```text
Super Admin promotes employee
        ↓
Designation updated
        ↓
Salary updated
        ↓
Salary History created
        ↓
Audit Trail created
        ↓
Activity/Notification generated
```

---

# 10. Audit Trail

The Audit Trail permanently records important actions performed in the system.

It answers:

> "What happened, who performed it, who was affected, and when?"

### Fields

| Field              | Description                             |
| ------------------ | --------------------------------------- |
| Audit ID           | Unique audit record identifier          |
| Date & Time        | Time when the action occurred           |
| Actor ID           | Person who performed the action         |
| Actor Role         | HR / Super Admin / other relevant role  |
| Action             | Action performed                        |
| Affected Person ID | Person affected by the action           |
| Details            | Additional information about the action |

### Example

```text
Audit ID: A001
Date & Time: 20-Sep-2026 09:15
Actor ID: HR002
Actor Role: HR
Action: Attendance Marked
Affected Person ID: E101
Details: Status changed to Present
```

### Important Rule

Audit records are generated **automatically by NOVA** when important actions occur. Users do not manually type audit entries.

---

# 11. Activity / Notification

The Activity/Notification Dashboard shows events that are relevant to a particular user.

It answers:

> "What happened that I should know about?"

### Fields

| Field                | Description                              |
| -------------------- | ---------------------------------------- |
| Activity ID          | Unique activity identifier               |
| Date & Time          | Time when the activity occurred          |
| Recipient ID         | User who should receive the activity     |
| Activity Type        | Type of event                            |
| Message              | Automatically generated notification     |
| Related Person ID    | Person related to the event              |
| Read / Unread Status | Whether the notification has been viewed |

### Examples

When attendance is marked:

```text
HR002 marked your attendance as Present.
```

When salary changes:

```text
Your salary has been increased from ₹30,000 to ₹35,000.
```

When salary is paid:

```text
Your salary for September 2026 has been marked as paid.
```

When an employee is promoted:

```text
You have been promoted from Junior Developer to Senior Developer.
```

### Activity Generation

Activity notifications are generated automatically by the system.

For example:

```text
Super Admin approves salary raise
             ↓
       ┌─────┴─────┐
       ↓           ↓
  Audit Trail   Activity
```

The Audit Trail records the detailed system action, while the Activity Dashboard provides the relevant user with a simpler notification.

---

# 12. Overall Data Relationship

The major relationships in NOVA are:

```text
                    Super Admin
                   /     |      \
                  /      |       \
             manages   approves   promotes
                /        |          \
               ↓         ↓           ↓
              HR    Raise Request   Employee
              │                         │
              │ rates                   │
              ↓                         │
          Performance ←─────────────────┘
                                         │
                    ┌────────────────────┼───────────────────┐
                    ↓                    ↓                   ↓
               Attendance         Salary History      Payment History
                    │                    │                   │
                    └────────────────────┴───────────────────┘
                                         │
                                  Audit + Activity
```

The Employee entity stores the employee's current information, while separate historical entities preserve changes and events over time.
