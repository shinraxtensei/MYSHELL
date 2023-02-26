# MYSHELL "as beautiful as a shell"
<p>This project is a custom shell implementation written in C that can handle most of the commands that bash can. It supports piping and redirection, environment variables, signal handling, and more.</p>
<h2>Features</h2>
<ul>
  <li>Run any command that can be run in bash</li>
  <li>Handle piping and redirection of input and output</li>
  <li>Manage environment variables</li>
  <li>Handle signals like SIGINT (Ctrl-C) and SIGTSTP (Ctrl-Z)</li>
  <li>Use terminal capabilities to display colored output and navigate through command history</li>
  <li>Autocomplete commands using the tab key</li>
  <li>Run commands in the background using the "&amp;" symbol</li>
</ul>
<h2>Getting Started</h2>
<p>To get started with this project, clone the repository to your local machine and navigate to the project directory. Compile the code by running the <code>make</code> command in the terminal.</p>
<p>Once the code is compiled, run the shell executable using the following command:</p>
<pre><code>$ ./shell</code></pre>
<p>This will start the shell and you can start entering commands.</p>
<h2>Usage</h2>
<p>This shell works just like any other shell. You can run any command that can be run in bash, including pipes and redirection.</p>
<h3>Piping</h3>
<p>To pipe the output of one command to another, use the "|" symbol. For example, to list all the files in the current directory and then sort them alphabetically, you can use the following command:</p>
<pre><code>$ ls -la | sort</code></pre>
<h3>Redirection</h3>
<p>To redirect the output of a command to a file, use the ">" symbol. For example, to save the output of the "ls" command to a file called "files.txt", you can use the following command:</p>
<pre><code>$ ls &gt; files.txt</code></pre>
<p>To append the output of a command to a file, use the ">>" symbol. For example, to append the output of the "ls" command to a file called "files.txt", you can use the following command:</p>
<pre><code>$ ls &gt;&gt; files.txt</code></pre>
<h3>Environment Variables</h3>
<p>To set an environment variable, use the "export" command. For example, to set the variable "MYVAR" to the value "hello", you can use the following command:</p>
<pre><code>$ export MYVAR=hello</code></pre>
<p>To see a list of all environment variables, use the "env" command. For example:</p>
<pre><code>$ env</code></pre>
<h3>Signal Handling</h3>
<p>This shell handles signals like SIGINT (Ctrl-C) and SIGTSTP (Ctrl-Z). To interrupt a running command, press Ctrl-C. To pause a running command, press Ctrl-Z.</p>
<h3>Autocomplete</h3>
<p>To autocomplete commands, press the tab key. The shell will attempt to complete the command based on the characters you've typed so far.</p>
<h3>Background Commands</h3>
<p>To run a command in the background, use the "&amp;" symbol at the end of the command. For example:</p>
<pre><code>$ sleep 10 &amp;</code></pre>
<p>This will run the "sleep 10" command in the background, allowing you to continue entering commands in the shell.</p>
<h3>Contributing</h3>
<p>If you have any ideas for new features or improvements to existing ones, feel free to submit a pull request.</p>
<h3>License</h3>
<p>This project is licensed under the MIT License - see the LICENSE file for details.</p>
