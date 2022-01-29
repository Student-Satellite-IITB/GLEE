How to use alsep-tools

0. OVERVIEW

The alsep-tools is a tool to extract data from Apollo Lunar Seismic Experiments Package (ALSEP).
The software is currently beta version.

1. INSTALLATION

$ tar zxvf alsep_tools-0.4.tar.gz
$ cd alsep_tools-0.4
$ ./configure
$ make
$ su 
# make install

2. PROGRAMS

pseinfo             ... extract PSE data from PSE tape
wtninfo             ... extract PSE and LSG data from WTN tape
wthinfo             ... extract LSPE data from WTH tape

pse2pgcopy          ... extract PSE data in PGCOPY format from PSE tape
wtn2pgcopy          ... extract PSE data in PGCOPY format from WTN tape
wtn2pgcopy_lsg      ... extract LSG data in PGCOPY format from WTN tape
wth2pgcopy          ... extract LSPE data in PGCOPY format from WTH tape

register_pse.sh     ... pse registering script using pse2pgcopy
register_wtn.sh     ... pse registering script using wtn2pgcopy
register_wtn_lsg.sh ... lsg registering script using wtn2pgcopy_lsg
register_wth.sh     ... wth registering script using wth2pgcopy

3. USAGE

3.1 pseinfo

The 'pseinfo' program shows extracted PSE data from a PSE tape.
Without any command-line options, the program shows a brief summary.

For instance,

$ pseinfo pse.a11.1.1
pse.a11.1.1,11,10001,1969,0,202,04:39:20.334,203,08:21:26.185,602

Each column means is listed in below:
filename,sequence number,year,format,start doy,start time,end doy,end time

The PSE tape has three hierarchy: Record, Frame, and Data. The detail is shown in
http://darts.isas.jaxa.jp/planet/seismology/apollo/PSE_Tape_Format.html
A File includes multiple records, and a record includes multiple frames.

Using -r option, you can obtain Record information in the following:

$ pseinfo -r pse.a.11.1.1

As well as -r option, -f and -d option show frame information and data body respectively.
For example,

$ pseinfo -rfd pse.a.11.1.1

3.2 wtninfo

The 'wtninfo' program  shows extracted PSE data from WTN tape.
Without command-line options, a brief summary is shown.

$ wtninfo wtn.1.1
wtn.1.1,7001,12345,1976,61,00:01:44.696,61,10:11:50.548,4965

The columns are slightly different from those of pseinfo:
filename,original 9-track tape ID number,active station code,year,start doy,start time,end doy,end time

-r, -f, and -d options are the same as pseinfo.

Unlike with PSE tape, WTN tape has multiple apollo stations in one file.
The 'active station code' shows the information of the included apollo stations:
For instance, 12345 means 1,2,3,4, and 5. Active station code 1,2,3,4, and 5 are corresponding to 
Apollo 12, 15, 16, 14, 17 stations respectively.

To extract a specific active station, you can use -p option.
Also -i option is available to ignore duplicated headers, which means that the original tape format
has sometimes wrong header in it.

3.3 wthinfo

wthinfo displays the extracted LSPE data from WTH tape.
The command-line options are the same as wtninfo options.


4. How to make database in postgresql

4.1 Prerequistes

OS: CentOS 6.0, or later
Database: PostgreSQL 8.4, or later
HDD: more than 1TB
Memory: more than 4GB

4.2 Installation

# yum -y install postgresql-server

4.2 Data structure

The following data structure is assumed:

/data/apollo/pse/ets
/data/apollo/pse/p11s
/data/apollo/pse/p12s
/data/apollo/pse/p14s
/data/apollo/pse/p15s
/data/apollo/pse/p16s
/data/apollo/pse/sets
/data/apollo/pse/wths
/data/apollo/pse/wtns

Note: /data/apollo directory requires HDD space more than 120GB 

4.3 Initialize PostgreSQL

If you already install PostgreSQL database and it works, skip this step. 
The following command will erase your all database you installed before.

# service postgresql initdb

The default setting, /var/lib/pgsql/data is used to store database.
The required capasity /var/lib/pgsql/data is more than 800GB.

4.4 Settings PostgreSQL

To enable access from localhost, change the setting in the pg_hba in the following:
# vi /var/lib/pgsql/data/pg_hba
before: host all all 127.0.0.1/32 ident
after:  host all all 127.0.0.1/32 trust

If you worried about the security, please set them appropriate.

4.5 Start PostgreSQL daemon

# service postgresql start

4.6 Create Database User

If your username is 'foo', execute the following command:

# createuser -d -R -S foo

4.6 Create database

You do not need to execute the following steps as a super user:

$ createdb apollo
$ createlang plpgsql apollo
$ psql apollo -f /usr/local/share/alsep_tools/init.sql
$ psql apollo -f /usr/local/share/alsep_tools/alsep_funcs.sql
$ psql apollo -f /usr/local/share/alsep_tools/events.sql
$ psql apollo -f /usr/local/share/alsep_tools/files.sql

4.7 Register Apollo data

The following steps take several hours, then you must do them carefully.

$ cd /data/apollo/pse
$ register_pse.sh | psql apollo
$ register_wtn.sh | psql apollo
$ register_wtn_lsg.sh | psql apollo
$ register_wth.sh | psql apollo
$ psql apollo -f /usr/local/share/alsep_tools/create_index.sql

4.8 Access the database

$ psql apollo
apollo=# SELECT * FROM tbl_pse LIMIT 100;
apollo=# SELECT * FROM tbl_lsg LIMIT 100;
apollo=# SELECT * FROM tbl_lspe LIMIT 100;
apollo=# SELECT * FROM event LIMIT 100;
apollo=# SELECT * FROM file LIMIT 100;

We also provide several funcitions in below:
apollo=# SELECT * FROM alsep_lp('1969-11-19T14:00:00',10000);
apollo=# SELECT * FROM alsep_sp('1969-11-19T14:00:00',10000);
apollo=# SELECT * FROM alsep_lsg('1977-05-01T00:00:00', 10000);
apollo=# SELECT * FROM alsep_lspe('1977-03-01T00:00:00', 10000);

The function requires two arguments: start time, and number of points.
The number of points also determine the end time from the start time using
sampling period, therefore, the number of points may be less than the specified one.

--- END ---
