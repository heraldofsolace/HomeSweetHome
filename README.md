# HomeSweetHome

[![GitHub Release](https://img.shields.io/github/release/heraldofsolace/HomeSweetHome.svg)](https://github.com/twpayne/heraldofsolace/HomeSweetHome)

A dotfile manager written in C++.

**Warning: Use at your own risk. I will not be held responsible if you break your setup.**

The code is not optimal. You can contribute by improving it.

## QuickStart

1. Initialize:

```shell
home_sweet_home init
```

This will set the source directory to `.local/share/home_sweet_home` and target directory to `~`

2. Add a file:

```shell
home_sweet_home add ~/.bashrc
```

This will copy `~/.bashrc` to `bashrc##hidden` in the source directory.

3. Edit:

```shell
home_sweet_home edit ~/.bashrc
```

This will edit the copy stored in source directory and not the actual file.

4. Apply when ready:

```shell
home_sweet_home apply ~/.bashrc
```

This will copy the updated file to the target directory.

5. (Optional) Add a template

```shell
home_sweet_home add ~/test -t
```

This will add the file `test` as a template with `.tmpl` extension.

```shell
home_seet_home edit ~/test
```

Put "Hello I am {{username}}" in the file and save.

```shell
home_sweet_home apply ~/test
```

Now `~/test` contains "Hello I am &lt;your username here&gt;".

To see the available data run

```shell
home_sweet_home data
```

The templating uses [Inja](https://github.com/pantor/inja) syntax.

## Installation

Coming soon.

## Donate

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/J3J53WCCI)
<a href="https://liberapay.com/heraldofsolace/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>