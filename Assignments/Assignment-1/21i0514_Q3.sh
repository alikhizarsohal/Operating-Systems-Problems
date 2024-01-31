
#!/bin/bash

# Print the name and roll number of the student.
echo "21-0514-Ali Khizar"

# Define a function to create a new user and assign administrator privileges to it.
user() {
  read -p "Enter username: " username
  read -s -p "Enter password: " password
  echo # Print a newline character to separate the password prompt from the next output.

  # Create the user.
  sudo useradd -m "$username"
  # Set the password for the user.
  echo "$username:$password" | sudo chpasswd
  # Add the user to the sudo group to grant administrator privileges.
  sudo usermod -aG sudo "$username"
  echo "User $username is created and administrator privileges are assigned."
}

# Define a function to list all installed applications.
apps() {
  # Use dpkg to list all installed packages and grep to filter out lines containing "ii" (which indicates an installed package).
  dpkg -l | grep "^ii"
}

# Define a function to install an application.
app() {
  read -p "Enter the name of the application to install: " app_name
  # Use apt-get to install the specified application.
  sudo apt-get install "$app_name"
}

# Define a function to set the IP address, mask, gateway, and DNS.
ip() {
  # Use ifconfig to set the IP address, mask, and gateway.
  sudo ifconfig eth0 10.0.0.1 netmask 255.255.255.0 gateway 10.0.0.254
  # Use echo to set the DNS server.
  echo "nameserver 8.8.8.8" | sudo tee /etc/resolv.conf >/dev/null
}

# Parse command line arguments.
while [[ $# -gt 0 ]]
do
  case "$1" in
    -uc|--user)
      user
      shift # Consume the -uc|--create-user argument.
      ;;
    -ld|--list-apps)
      apps
      shift # Consume the -ld|--list-apps argument.
      ;;
    -ins|--install-app)
      app
      shift # Consume the -ins|--install-app argument.
      ;;
    -ipcon|--set-ip-config)
      ip
      shift # Consume the -ipcon|--set-ip-config argument.
      ;;
    -h|--help)
      # Print the usage message and exit.
      echo "Usage: $0 [-uc|--user] [-ld|--list-apps] [-ins|--install-app] [-ipcon|--set-ip-config] [-h|--help]"
      exit 0
      ;;
    *)
      # Print an error message and exit if an unknown argument is provided.
      echo "Error: unknown argument $1"
      echo "Usage: $0 [-uc|--user] [-ld|--list-apps] [-ins|--install-app] [-ipcon|--set-ip-config] [-h|--help]"
      exit 1
      ;;
  esac
done

# Exit successfully if no arguments are provided.
exit 0
