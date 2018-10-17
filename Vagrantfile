Vagrant.configure("2") do |config|
  config.vm.box = "centos/7"
  config.vm.hostname = "cs3520-nogui"

  if Vagrant.has_plugin?("vagrant-vbguest")
    config.vm.synced_folder ".", "/vagrant", type: "virtualbox"
  end

  config.vm.provision "shell", inline: <<-SHELL
    yum install -y gcc-c++
    yum install -y gdb
    yum install -y valgrind
    yum install -y git
    yum install -y zip
    yum install -y unzip
    yum install -y emacs-nox
    yum install -y java-devel
  SHELL
end
