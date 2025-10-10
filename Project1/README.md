Hello There!

This is the README for project 1, where I'll briefly explain all 4 of the phases. Since more detailed explanations will be in the LaTeX document, I'll use the README as a more informal description of the project.

**Where to access**
To access the Project files, please head to the "Project 1" branch in this repo.

**Quick Overview**
For this project, we ran 4 phases.
- Phase 1 demonstrates the basics of parallel programming by implementing a basic bank system, where multiple threads attempt to deposit from different acconuts. This creates race conditions.
- Phase 2 demonstrates resource protection, creating locks to limit the use of a shared resource to one thread at a time. This solves the race conditions seen in phase 1.
- Phase 3 demonstrates how locking shared resources may result in a deadlock. In it, two separate accounts attempt transfering money to each other. Since two different threads lock their own balance while attempting to access the other account's balance, they both wait for the resource to be freed, while keeping their own locked. Thus, a Deadlock!
- Phase 4 aims to solve the deadlock issue with multiple approaches. For instance, extra logic is added to the codebase to ensure that some resources are prioritized, avoiding deadlocks. A different approach uses temporary locks to ensure that, if a deadlock occurs, the resources will be freed at some point during runtime.


For more details on this project, please read the LaTeX document detailing each phase, along with the approach taken, and the challenges phased.
