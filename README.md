# td - A simple Todo list manager

This is a cli todo manager I wrote in C to learn about storing changes in memory
before writing it to a file.

# Important

Please create a ~/.config/td/td.data file; this is where td stores your todo list.

# Usage

- To print current todo list run:
  ```
  p
  ```

- To add a todo run:
  ```
  a [name] [0-1]
  ```

- To change the value of a todo run:
  ```
  c [index] [0-1]
  ```
- To delete a todo run:
  ```
  d [index]
  ```
