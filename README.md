Dataset
=======

[15 minute readings of NCEI's COOP HPD Data from 2014 - March
2019][0]

Download, extract, and then concatonate all files together into a single
CSV.

To ensure a consistent document, [this][2] pre-concatonated tarball will be used
for testing.

Reference the dataset's
[README][1]
for an understanding of the csv headings.

Challenge
=========

Find the station north of the 45th parallel which experienced the
longest time with rain (not total rainfall, but total time raining).
Treat each `*Val` as a full 15 minutes.

Answer
======

Stations are labeled ABC123456789. Return just the numbers of the
station. If multiple stations experienced the same duration of rain for
the time period the dataset covers, return the sum of all station IDs
(stripped of letters).

For example:

If stations ABC12345 and stations DEF67890 share the longest duration of
rain than the answer would be:

80235

How to time
===========

Because tests will be performed on the same machine, and to accomdate
for answers which stream the data instead of reading it into memory,
begin timing immediately when your program starts and end timing
immediately after getting the result (I recommend passing `result`
back to `main()` so that the time to `printf()` doesn't count
against you).

``` {.Python}
if __name__ == "__main__":
    start = time.now()
    result = do_work()
    total_time = time.now() - start
    print(result)
```

Output
======

In order to automate the updating of the leaderboard output should be
formated accordingly:

``` {.csv}
Author, Language, Result, Time, Notes
```

Notes can include the method used to get the result (for example if you
have multiple answers)

How to Contribute
=================

Copy the example folder to a new folder (e.g. 'elixir/' for a elixir based test).  In the new folder put your build command (if any) in `build_test.sh` and put your run command in `run_test.sh`. If you are familiar with Docker place any dependancies in the Dockerfile.

How to run tests
================

All tests can be run locally using `run_tests.sh`. If you have docker installed you can build all tests using `build_docker_tests.sh`, then run using `run_docker_test.sh`. Docker will manage the test dependancies for you.

Individual tests can be run from their folders using `build_test.sh` and `run_test.sh` or, for Docker, `build_docker.sh` and `run_docker.sh`

Leaderboard
===========

## Single Threaded

| Name | Language | Answer | Time | Notes |
|------|----------|-------:|-----:|-------|
| plusuncold | C++          |   353402 |   8,336ms | optimized |
| pard68     | rust         | 00353402 |  20,788ms | |
| plusuncold | C++          |   353402 |  40,528ms | simple |
| zombeej    | Node v11.3.0 |   353402 |  52,898ms | Single-threaded & slow as molasses |
| specs      | python       | 00353402 |  61,070ms | ugly. needs cleanup. |
| specs      | cython       | 00353402 | 105,690ms | ugly. needs cleanup. | 

## Concurrent


| Name | Language | Answer | Time | Notes |
|------|----------|--------|------|-------|
| zombeej | Node v11.3.0 | 353402 | 22,064ms | Multi-threaded |

[0]: https://xe.pw/6emD
[1]: https://xe.pw/6emC
[2]: https://www.0x44.pw/trdc/201905challenge.tar.gz
