//
// Created by aniket on 09/03/2021.
//
#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <stdexcept>
#include <cstring>
#include <array>
#include <sys/wait.h>
#include "shell_command.h"

void shell_command::execute() {
  const int READ_END = 0;
  const int WRITE_END = 1;

  int infd[2] = {0, 0};
  int outfd[2] = {0, 0};
  int errfd[2] = {0, 0};

  auto cleanup = [&]() {
    close(infd[READ_END]);
    close(infd[WRITE_END]);

    close(outfd[READ_END]);
    close(outfd[WRITE_END]);

    close(errfd[READ_END]);
    close(errfd[WRITE_END]);
  };

  auto rc = pipe(infd);
  if(rc < 0)
  {
    throw std::runtime_error(std::strerror(errno));
  }

  rc = ::pipe(outfd);
  if(rc < 0)
  {
    close(infd[READ_END]);
    close(infd[WRITE_END]);
    throw std::runtime_error(std::strerror(errno));
  }

  rc = pipe(errfd);
  if(rc < 0)
  {
    close(infd[READ_END]);
    close(infd[WRITE_END]);

    close(outfd[READ_END]);
    close(outfd[WRITE_END]);
    throw std::runtime_error(std::strerror(errno));
  }

  auto pid = fork();
  if(pid > 0) // PARENT
  {
    close(infd[READ_END]);    // Parent does not read from stdin
    close(outfd[WRITE_END]);  // Parent does not write to stdout
    close(errfd[WRITE_END]);  // Parent does not write to stderr

    if(write(infd[WRITE_END], std_in.data(), std_in.size()) < 0)
    {
      throw std::runtime_error(std::strerror(errno));
    }
    close(infd[WRITE_END]); // Done writing
  }
  else if(pid == 0) // CHILD
  {
    dup2(infd[READ_END], STDIN_FILENO);
    dup2(outfd[WRITE_END], STDOUT_FILENO);
    dup2(errfd[WRITE_END], STDERR_FILENO);

    close(infd[WRITE_END]);   // Child does not write to stdin
    close(outfd[READ_END]);   // Child does not read from stdout
    close(errfd[READ_END]);   // Child does not read from stderr

    execl("/bin/bash", "bash", "-c", command.c_str(), nullptr);
    exit(EXIT_SUCCESS);
  }

  // PARENT
  if(pid < 0)
  {
    cleanup();
    throw std::runtime_error("Failed to fork");
  }

  int status = 0;
  waitpid(pid, &status, 0);

  std::array<char, 256> buffer;

  ssize_t bytes = 0;
  do
  {
    bytes = read(outfd[READ_END], buffer.data(), buffer.size());
    std_out.append(buffer.data(), bytes);
  }
  while(bytes > 0);

  do
  {
    bytes = read(errfd[READ_END], buffer.data(), buffer.size());
    std_err.append(buffer.data(), bytes);
  }
  while(bytes > 0);

  if(WIFEXITED(status))
  {
    exit_status = WEXITSTATUS(status);
  }

  cleanup();
}
