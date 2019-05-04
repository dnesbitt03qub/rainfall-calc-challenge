use std::{env, fs, io, io::{prelude::*, BufReader}, time};
use std::collections::HashMap;

fn main() -> io::Result<()> {
    let start = time::Instant::now();

    let filename = env::args().nth(1).unwrap();
    let file = fs::File::open(filename)?;
    let reader = BufReader::new(file);

    let mut durations = HashMap::new();

    for line in reader.lines() {
        let buffer = line.unwrap();
        let lat_data: String = buffer.chars().skip(12).take(2).collect();
        let lat_data = lat_data.parse::<usize>();
        let lat = match lat_data {
            Ok(lat) => lat,
            Err(_err) => 0,
        };
        if lat >= 45 {
            let items: Vec<&str> = buffer.split(',').collect();
            //iterate through values, starting at 6 and stepping by 5
            //until gone through 96 values, aka through the 481st item
            for interval in (6..481).step_by(5) {
                if items[interval] != "0".to_string() && items[interval] != "-9999".to_string() {
                    let counter = durations.entry(items[0].to_string()).or_insert(0);
                    *counter += 15;
                }
            }
        }
    }
    let mut sorted: Vec<_> = durations.iter().collect();
    sorted.sort_by(|a, b| a.1.cmp(b.1).reverse());
    let result: String = sorted[0].0.to_string();
    let result: Vec<_> = result.split("USC").collect();
    //let result = sorted[0].0;

    let elapsed = start.elapsed();
    let seconds = ((elapsed.as_secs() as f64) + (elapsed.subsec_nanos() as f64 / 1_000_000_000.0)) * 1000.0;
    //println!("{:#?}", sorted);
    println!("pard68, rust, {}, {}", result[1], seconds);

    Ok(())
}
