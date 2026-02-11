# TodoList
📝 ToDo CLI - C Language Task Manager

A powerful command-line todo list application written in C with dual data structures and comprehensive backup/recovery system.

https://img.shields.io/badge/language-C-blue
https://img.shields.io/badge/license-MIT-green

🔍 Overview

ToDo CLI is a robust task management solution built from scratch in pure C. Unlike typical todo apps that rely on high-level languages, this implementation demonstrates advanced C programming concepts including dynamic memory allocation, file I/O operations, buffer management, and custom string handling - all while delivering a smooth user experience.

✨ Features

Core Functionality

· ✅ Add Tasks - Create new todos with unlimited length
· ✏️ Edit Tasks - Modify existing tasks by ID
· 🗑️ Delete Tasks - Remove tasks with automatic array shifting
· ✅ Mark as Done - Move completed tasks to separate archive
· 📋 List All - View both pending and completed tasks
· 💾 Manual Backup - Export data to text files
· 🔄 Restore Backup - Import from previously saved files
· 🧹 Auto Cleanup - Memory sanitization on exit

Advanced Features

· Dual-list architecture - Separate arrays for pending/completed tasks
· Real-time buffer cleaning - Prevents input overflow
· Case-insensitive commands - Accepts ADD, Add, add equally
· Memory leak prevention - All malloc() calls have corresponding free()
· Comprehensive error messages - User-friendly error handling

🏗️ Data Structures

Primary Storage

```c
struct Main_List {
    string todo;
} todos_list[100];
```

Completed Tasks Archive

```c
struct Done_List {
    string done;
} Done_L[100];
```

Why two structures? This separation enables clean visualization, efficient memory management, organized backups, and optimized O(n) operations.

📖 Usage Guide

Complete Workflow Example

```bash
$ ./todo
choose one of the operators for your todo list (add/edit/done/ls/del/backup/exit):

> add
what do you want to add in your todo list
Complete C project documentation
Added: Complete C project documentation

> add
what do you want to add in your todo list
Review pull requests
Added: Review pull requests

> ls
1-Complete C project documentation
2-Review pull requests
DONE:
there is nothing to show

> done
choose your done task for the day
1-Complete C project documentation
2-Review pull requests
> 1
task is done as: Complete C project documentation

> ls
1-Review pull requests
DONE:
1-Complete C project documentation

> backup
give me a location of your backup (use double\\ to use back slash notation):
C:\\Users\\YourName\\todo_backup.txt
backup has been created in this location: C:\\Users\\YourName\\todo_backup.txt
```

💾 Backup System

Creating Backups

The program generates human-readable text files with this structure:

```
=======TODO TASK=======
1.Review pull requests
=========DONE TASK=======
1.Complete C project documentation
```

Restoring Backups

```bash
> backup
give me a location of your backup:
C:\\backups\\my_tasks.txt
Loaded 3 todos from backup.
Total todos now: 3
```

🧠 Memory Management

This project demonstrates professional-grade memory handling:

Allocation Strategy

```c
todos_list[num_todo].todo = malloc(strlen(append) + 1);
```

Deallocation Guarantees

· DEL command: free() on specific index before shifting
· DONE command: free() on original, new allocation for archive
· CLEAN function: Systematic freeing of ALL pointers
· NULL assignment: Prevents dangling pointers

Buffer Security

```c
int BUFFER_CLEANER() {
    while (getchar() != '\n');
}
```

⚠️ Error Handling

Comprehensive error checking at every stage:

```c
// Memory allocation failure
if (todos_list[num_todo].todo == NULL) {
    printf("memory allocation has failed please try again later!!!\n");
    return 1;
}

// Array bounds checking
if (index < 0 || index >= num_todo) {
    printf("not valid\n");
    return 1;
}

// File operations
if (backup_todo == NULL) {
    printf("couldnt allocate the folder please try again !!!!\n");
    return 1;
}
```

🚀 Performance Characteristics

Operation Time Complexity Notes
ADD O(1) Simple array append
DELETE O(n) Shifting required
DONE O(n) Remove + archive
EDIT O(1) Direct index access
LS O(n) Full traversal
BACKUP O(n) File write operation

🔧 Customization Guide

Increase Capacity

```c
struct Main_List todos_list[500];  // Was 100
struct Done_List Done_L[500];      // Was 100
```

Add Priority System

```c
struct Main_List {
    string todo;
    int priority;
};
```

🤝 Contributing

Contributions welcome! Areas for improvement:

· 🔲 Linked list implementation - Replace static arrays
· 🔲 Color coding - ANSI colors for priority levels
· 🔲 Search functionality - Filter tasks by keyword
· 🔲 JSON backup format - Better interoperability
· 🔲 Unit tests - Automated testing suite

📄 License

MIT

---

<div align="center">⭐ Star this repo • 🐛 Report Bug

Made with ❤️ and pure C

</div>
