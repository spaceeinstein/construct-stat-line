# Construct Stat Line

## Introduction

*Construct Stat Line* is a plugin for Grand Theft Auto: Vice City. Its primary aim is to replace the entire internal function that constructs each line in the game's statistics menu. This replacement makes it far easier to change the way the game displays each line like fixing any bugs that were introduced by the developers of the game and customizing values that were hardcoded by the developers. The secondary aim of the plugin is to allow any number of custom plugins to add their own lines into the statistics menu.

## Bug fixes

* Percentage completed

  Fixes an edge case where it is possible to set up a division by zero for this statistic. Previously this division by zero could occur if the [total progress](http://www.gtamodding.com/wiki/030D) was set to 1 and the [current progress](http://www.gtamodding.com/wiki/030C) was set to 0 through the script, and the game language was set to French or German. This caused the game to display the value of the statistic as `-2147483648%` (0x80000000).

* Hidden Packages found

  Replaces the hardcoded total number of packages of 100 with the value set by the script. It also removes the calculations done to display the correct ratio. Previously the game ignored the [total number set through the script](http://www.gtamodding.com/wiki/02ED) but it did display the correct ratio if the total was not 100, e.g. if the actual total was 3 and the player collected the first package, the game displayed the statistic as `33 out of 100`.

* Dist. traveled in miles

  Uses a more accurate conversion from meters to miles by multiplying the measurement in meters by 0.0006213712. Previously the game converted the measurements, which are stored in meters, to miles by multiplying them by 0.0005988024.

* Total distance traveled

  Includes the distance traveled by plane to the total distance traveled in miles, and distances traveled by bike and plane to the total distance traveled in meters. Previously the game omitted those distances from the total.

* Max. INSANE Jump

  Displays INSANE jump distance and height measurements in feet when in non-metric units. Previously the game displayed the two measurements only in meters.

* Pilot Ranking

  Fixes numerous issues with the way the game displayed pilot ranking. This was discussed in a [topic on GTAForums.com](http://gtaforums.com/topic/798160-).

* Most Favorite Radio Station

  Fixes the possibility of showing the MP3 player station as the most favorite radio station if it is not available. Previously if your most listened station was the MP3 player station, which allowed the game show it as your favorite radio station, and then completely removed all your MP3s to cause the station to not show up as selectable, the MP3 player station remained shown as your favorite radio station.

* Least Favorite Radio Station

  Fixes the possibility of showing the Wave 103 station as the least favorite radio station if the MP3 player station is not available. Previously if the MP3 player station was not selectable, the game defaulted to Wave 103 as the least favorite radio station.

* Favorite Radio Station

  Fixes the possibility of showing a radio station be both the most and least favorite radio station. This is a rare edge case but previously if the listening time for all radio stations were the same, the game chose to show Wildstyle as both the most and least favorite.

## Customizations

The `construct-stat-line.ini` file allows you to customize various settings of the plugin and the display behaviors of some default stats. You can reload the plugin and its settings in-game by pressing the "R" key while in the statistics menu.

```ini
[Main]
ReloadKey=0x52
UseDefaultStats=1
UseCustomStats=1

[DefaultStats]
MetricOnly=0
TotalStoresKnockedOff=15
TotalMovieStunts=0
TotalAssassinations=5
```

* `ReloadKey`

  You can change the reload key from the default key of "R" to any [virtual-key code](https://msdn.microsoft.com/en-us/library/dd375731(VS.85).aspx).

* `UseDefaultStats`

  Set this to "1" to use the default stats from the base game or "0" to not use it.

* `UseCustomStats`

  Set this to "1" to use stats from custom plugins or "0" to not use it.

* `MetricOnly`

  Set this to "1" to use metric units in the default stats when set to the English language or "0" to not use it.

* `TotalStoresKnockedOff`

  Use this option to set the total number of stores to knock off, which is normally not possible to set through the script.

* `TotalMovieStunts`

  Use this option to set the total number of movie stunts, which is normally not possible to set through the script.

* `TotalAssassinations`

  Use this option to set the total number of assassinations, which is normally not possible to set through the script.
