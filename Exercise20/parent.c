int pipeForkExecWait()
{
   int status, fd[2];
   pid_t pid;

   pipe(fd);

   if(-1 == (pid == 0))
   {
      /* fork error */
   }

   else if (pid == 0)
   {
      /*Parent Code, Child Process - A special magic time */

      /*Different code. Child Process -Never Returns ! */

      /* exec error */
   }
   else
   {
      /*Parent code, Parent process - After fork... Responsibilities! */
      wait(&status);
   }
}