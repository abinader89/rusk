Vagrant.configure("2") do |config|
  config.vm.box = "centos/7"
  config.vm.hostname = "cs3520-gui"

  if Vagrant.has_plugin?("vagrant-vbguest")
    config.vm.synced_folder ".", "/vagrant", type: "virtualbox"
  end

  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.memory = 4096
    vb.cpus = 2
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

    yum install -y hg

    yum groupinstall -y 'gnome desktop'
    yum install -y 'xorg*'
    yum remove -y initial-setup initial-setup-gui

    systemctl isolate graphical.target
    systemctl set-default graphical.target

    yum install -y centos-release-scl
    yum-config-manager --enable rhel-server-rhscl-7-rpms
    yum install -y rh-eclipse46
    scl enable rh-eclipse46 bash

    echo password | sudo passwd vagrant --stdin

    for rpm in \
        SDL2-2.0.8-5.el7.x86_64.rpm \
        SDL2-devel-2.0.8-5.el7.x86_64.rpm \
        SDL2_ttf-2.0.14-2.el7.x86_64.rpm \
        SDL2_ttf-devel-2.0.14-2.el7.x86_64.rpm \
        SDL2_image-2.0.3-1.el7.x86_64.rpm \
        SDL2_image-devel-2.0.3-1.el7.x86_64.rpm \
        SDL2_mixer-2.0.2-2.el7.x86_64.rpm \
        SDL2_mixer-devel-2.0.2-2.el7.x86_64.rpm
    do
      wget http://dl.fedoraproject.org/pub/epel/7/x86_64/Packages/s/${rpm}
      yum localinstall -y ${rpm}
      rm ${rpm}
    done
  SHELL
end
