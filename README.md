# Haris Konstadinidis — Portfolio

Systems-oriented software engineer in training at [Codam](https://codam.nl) (42 Network), with a background leading operations and teams before moving into software. I build things by understanding how they actually work underneath — this repo is the C/Unix systems work that came out of that.

[GitHub](https://github.com/hariskonstadinidis) · [LinkedIn](https://www.linkedin.com/in/hariskon/) · haris_konstadinidis@protonmail.com

## Projects

| Project | What it is | Demonstrates |
|---|---|---|
| [Minishell](./Minishell) | A working Unix shell: parsing, pipes, redirections, heredocs, built-ins, signals | Process management, Unix internals, debugging with GDB, teamwork |
| [Philosophers](./Philosophers) | The Dining Philosophers problem solved with threads and mutexes | Concurrency, deadlock avoidance, precise timing under threads |
| [Pipex](./Pipex) | `cmd1 \| cmd2` reimplemented by hand with `fork`, `pipe`, `dup2`, `execve` | Process creation, file descriptors, PATH resolution |
| [miniRT](./miniRT) | A ray tracer rendering spheres, planes, and capped cylinders with lighting and shadows | Vector math, 3D geometry, graphics pipeline |

Every project folder has its own README with the architecture, the hard parts, the design decisions behind them, and what I'd do differently. These are Codam/42 curriculum projects — built, debugged, and evaluated by hand, not generated. Minishell and miniRT were team projects of two; Philosophers and Pipex are solo work.

## Why these projects

Each one forces a different kind of systems thinking: Minishell and Pipex are about processes and the OS, Philosophers is about concurrency, miniRT is about math and reading someone else's architecture before touching it. Together they're a more honest signal of how I think through a problem than any single one on its own.

## Background

Before Codam, I spent several years at a bike courier company in the Netherlands, working up from courier to assistant manager to manager — running day-to-day operations, planning, scheduling, and team development. That's where the systems-thinking habit actually started: most of the job was finding where a process was quietly broken and fixing it. Codam is where I started applying that to software instead.
