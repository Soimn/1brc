#include <windows.h>
#include <intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef signed __int8  s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef u8 bool;
#define true 1
#define false 0

typedef double f64;

#define ASSERT(EX) ((EX) ? 1 : (*(volatile int*)0 = 0))

#define ARRAY_SIZE(A) (sizeof(A)/sizeof(0[A]))

typedef struct String
{
  u8* data;
  u32 len;
} String;

#define STRING(S) (String){ .data = (u8*)(S), .len = sizeof(S)-1 }
#define MS_STRING(S) { .data = (u8*)(S), .len = sizeof(S)-1 }

String WeatherStations[] = {
  MS_STRING("Abha"),
  MS_STRING("Abidjan"),
  MS_STRING("Abéché"),
  MS_STRING("Accra"),
  MS_STRING("Addis Ababa"),
  MS_STRING("Adelaide"),
  MS_STRING("Aden"),
  MS_STRING("Ahvaz"),
  MS_STRING("Albuquerque"),
  MS_STRING("Alexandra"),
  MS_STRING("Alexandria"),
  MS_STRING("Algiers"),
  MS_STRING("Alice Springs"),
  MS_STRING("Almaty"),
  MS_STRING("Amsterdam"),
  MS_STRING("Anadyr"),
  MS_STRING("Anchorage"),
  MS_STRING("Andorra la Vella"),
  MS_STRING("Ankara"),
  MS_STRING("Antananarivo"),
  MS_STRING("Antsiranana"),
  MS_STRING("Arkhangelsk"),
  MS_STRING("Ashgabat"),
  MS_STRING("Asmara"),
  MS_STRING("Assab"),
  MS_STRING("Astana"),
  MS_STRING("Athens"),
  MS_STRING("Atlanta"),
  MS_STRING("Auckland"),
  MS_STRING("Austin"),
  MS_STRING("Baghdad"),
  MS_STRING("Baguio"),
  MS_STRING("Baku"),
  MS_STRING("Baltimore"),
  MS_STRING("Bamako"),
  MS_STRING("Bangkok"),
  MS_STRING("Bangui"),
  MS_STRING("Banjul"),
  MS_STRING("Barcelona"),
  MS_STRING("Bata"),
  MS_STRING("Batumi"),
  MS_STRING("Beijing"),
  MS_STRING("Beirut"),
  MS_STRING("Belgrade"),
  MS_STRING("Belize City"),
  MS_STRING("Benghazi"),
  MS_STRING("Bergen"),
  MS_STRING("Berlin"),
  MS_STRING("Bilbao"),
  MS_STRING("Birao"),
  MS_STRING("Bishkek"),
  MS_STRING("Bissau"),
  MS_STRING("Blantyre"),
  MS_STRING("Bloemfontein"),
  MS_STRING("Boise"),
  MS_STRING("Bordeaux"),
  MS_STRING("Bosaso"),
  MS_STRING("Boston"),
  MS_STRING("Bouaké"),
  MS_STRING("Bratislava"),
  MS_STRING("Brazzaville"),
  MS_STRING("Bridgetown"),
  MS_STRING("Brisbane"),
  MS_STRING("Brussels"),
  MS_STRING("Bucharest"),
  MS_STRING("Budapest"),
  MS_STRING("Bujumbura"),
  MS_STRING("Bulawayo"),
  MS_STRING("Burnie"),
  MS_STRING("Busan"),
  MS_STRING("Cabo San Lucas"),
  MS_STRING("Cairns"),
  MS_STRING("Cairo"),
  MS_STRING("Calgary"),
  MS_STRING("Canberra"),
  MS_STRING("Cape Town"),
  MS_STRING("Changsha"),
  MS_STRING("Charlotte"),
  MS_STRING("Chiang Mai"),
  MS_STRING("Chicago"),
  MS_STRING("Chihuahua"),
  MS_STRING("Chișinău"),
  MS_STRING("Chittagong"),
  MS_STRING("Chongqing"),
  MS_STRING("Christchurch"),
  MS_STRING("City of San Marino"),
  MS_STRING("Colombo"),
  MS_STRING("Columbus"),
  MS_STRING("Conakry"),
  MS_STRING("Copenhagen"),
  MS_STRING("Cotonou"),
  MS_STRING("Cracow"),
  MS_STRING("Da Lat"),
  MS_STRING("Da Nang"),
  MS_STRING("Dakar"),
  MS_STRING("Dallas"),
  MS_STRING("Damascus"),
  MS_STRING("Dampier"),
  MS_STRING("Dar es Salaam"),
  MS_STRING("Darwin"),
  MS_STRING("Denpasar"),
  MS_STRING("Denver"),
  MS_STRING("Detroit"),
  MS_STRING("Dhaka"),
  MS_STRING("Dikson"),
  MS_STRING("Dili"),
  MS_STRING("Djibouti"),
  MS_STRING("Dodoma"),
  MS_STRING("Dolisie"),
  MS_STRING("Douala"),
  MS_STRING("Dubai"),
  MS_STRING("Dublin"),
  MS_STRING("Dunedin"),
  MS_STRING("Durban"),
  MS_STRING("Dushanbe"),
  MS_STRING("Edinburgh"),
  MS_STRING("Edmonton"),
  MS_STRING("El Paso"),
  MS_STRING("Entebbe"),
  MS_STRING("Erbil"),
  MS_STRING("Erzurum"),
  MS_STRING("Fairbanks"),
  MS_STRING("Fianarantsoa"),
  MS_STRING("Flores,  Petén"),
  MS_STRING("Frankfurt"),
  MS_STRING("Fresno"),
  MS_STRING("Fukuoka"),
  MS_STRING("Gabès"),
  MS_STRING("Gaborone"),
  MS_STRING("Gagnoa"),
  MS_STRING("Gangtok"),
  MS_STRING("Garissa"),
  MS_STRING("Garoua"),
  MS_STRING("George Town"),
  MS_STRING("Ghanzi"),
  MS_STRING("Gjoa Haven"),
  MS_STRING("Guadalajara"),
  MS_STRING("Guangzhou"),
  MS_STRING("Guatemala City"),
  MS_STRING("Halifax"),
  MS_STRING("Hamburg"),
  MS_STRING("Hamilton"),
  MS_STRING("Hanga Roa"),
  MS_STRING("Hanoi"),
  MS_STRING("Harare"),
  MS_STRING("Harbin"),
  MS_STRING("Hargeisa"),
  MS_STRING("Hat Yai"),
  MS_STRING("Havana"),
  MS_STRING("Helsinki"),
  MS_STRING("Heraklion"),
  MS_STRING("Hiroshima"),
  MS_STRING("Ho Chi Minh City"),
  MS_STRING("Hobart"),
  MS_STRING("Hong Kong"),
  MS_STRING("Honiara"),
  MS_STRING("Honolulu"),
  MS_STRING("Houston"),
  MS_STRING("Ifrane"),
  MS_STRING("Indianapolis"),
  MS_STRING("Iqaluit"),
  MS_STRING("Irkutsk"),
  MS_STRING("Istanbul"),
  MS_STRING("İzmir"),
  MS_STRING("Jacksonville"),
  MS_STRING("Jakarta"),
  MS_STRING("Jayapura"),
  MS_STRING("Jerusalem"),
  MS_STRING("Johannesburg"),
  MS_STRING("Jos"),
  MS_STRING("Juba"),
  MS_STRING("Kabul"),
  MS_STRING("Kampala"),
  MS_STRING("Kandi"),
  MS_STRING("Kankan"),
  MS_STRING("Kano"),
  MS_STRING("Kansas City"),
  MS_STRING("Karachi"),
  MS_STRING("Karonga"),
  MS_STRING("Kathmandu"),
  MS_STRING("Khartoum"),
  MS_STRING("Kingston"),
  MS_STRING("Kinshasa"),
  MS_STRING("Kolkata"),
  MS_STRING("Kuala Lumpur"),
  MS_STRING("Kumasi"),
  MS_STRING("Kunming"),
  MS_STRING("Kuopio"),
  MS_STRING("Kuwait City"),
  MS_STRING("Kyiv"),
  MS_STRING("Kyoto"),
  MS_STRING("La Ceiba"),
  MS_STRING("La Paz"),
  MS_STRING("Lagos"),
  MS_STRING("Lahore"),
  MS_STRING("Lake Havasu City"),
  MS_STRING("Lake Tekapo"),
  MS_STRING("Las Palmas de Gran Canaria"),
  MS_STRING("Las Vegas"),
  MS_STRING("Launceston"),
  MS_STRING("Lhasa"),
  MS_STRING("Libreville"),
  MS_STRING("Lisbon"),
  MS_STRING("Livingstone"),
  MS_STRING("Ljubljana"),
  MS_STRING("Lodwar"),
  MS_STRING("Lomé"),
  MS_STRING("London"),
  MS_STRING("Los Angeles"),
  MS_STRING("Louisville"),
  MS_STRING("Luanda"),
  MS_STRING("Lubumbashi"),
  MS_STRING("Lusaka"),
  MS_STRING("Luxembourg City"),
  MS_STRING("Lviv"),
  MS_STRING("Lyon"),
  MS_STRING("Madrid"),
  MS_STRING("Mahajanga"),
  MS_STRING("Makassar"),
  MS_STRING("Makurdi"),
  MS_STRING("Malabo"),
  MS_STRING("Malé"),
  MS_STRING("Managua"),
  MS_STRING("Manama"),
  MS_STRING("Mandalay"),
  MS_STRING("Mango"),
  MS_STRING("Manila"),
  MS_STRING("Maputo"),
  MS_STRING("Marrakesh"),
  MS_STRING("Marseille"),
  MS_STRING("Maun"),
  MS_STRING("Medan"),
  MS_STRING("Mek'ele"),
  MS_STRING("Melbourne"),
  MS_STRING("Memphis"),
  MS_STRING("Mexicali"),
  MS_STRING("Mexico City"),
  MS_STRING("Miami"),
  MS_STRING("Milan"),
  MS_STRING("Milwaukee"),
  MS_STRING("Minneapolis"),
  MS_STRING("Minsk"),
  MS_STRING("Mogadishu"),
  MS_STRING("Mombasa"),
  MS_STRING("Monaco"),
  MS_STRING("Moncton"),
  MS_STRING("Monterrey"),
  MS_STRING("Montreal"),
  MS_STRING("Moscow"),
  MS_STRING("Mumbai"),
  MS_STRING("Murmansk"),
  MS_STRING("Muscat"),
  MS_STRING("Mzuzu"),
  MS_STRING("N'Djamena"),
  MS_STRING("Naha"),
  MS_STRING("Nairobi"),
  MS_STRING("Nakhon Ratchasima"),
  MS_STRING("Napier"),
  MS_STRING("Napoli"),
  MS_STRING("Nashville"),
  MS_STRING("Nassau"),
  MS_STRING("Ndola"),
  MS_STRING("New Delhi"),
  MS_STRING("New Orleans"),
  MS_STRING("New York City"),
  MS_STRING("Ngaoundéré"),
  MS_STRING("Niamey"),
  MS_STRING("Nicosia"),
  MS_STRING("Niigata"),
  MS_STRING("Nouadhibou"),
  MS_STRING("Nouakchott"),
  MS_STRING("Novosibirsk"),
  MS_STRING("Nuuk"),
  MS_STRING("Odesa"),
  MS_STRING("Odienné"),
  MS_STRING("Oklahoma City"),
  MS_STRING("Omaha"),
  MS_STRING("Oranjestad"),
  MS_STRING("Oslo"),
  MS_STRING("Ottawa"),
  MS_STRING("Ouagadougou"),
  MS_STRING("Ouahigouya"),
  MS_STRING("Ouarzazate"),
  MS_STRING("Oulu"),
  MS_STRING("Palembang"),
  MS_STRING("Palermo"),
  MS_STRING("Palm Springs"),
  MS_STRING("Palmerston North"),
  MS_STRING("Panama City"),
  MS_STRING("Parakou"),
  MS_STRING("Paris"),
  MS_STRING("Perth"),
  MS_STRING("Petropavlovsk-Kamchatsky"),
  MS_STRING("Philadelphia"),
  MS_STRING("Phnom Penh"),
  MS_STRING("Phoenix"),
  MS_STRING("Pittsburgh"),
  MS_STRING("Podgorica"),
  MS_STRING("Pointe-Noire"),
  MS_STRING("Pontianak"),
  MS_STRING("Port Moresby"),
  MS_STRING("Port Sudan"),
  MS_STRING("Port Vila"),
  MS_STRING("Port-Gentil"),
  MS_STRING("Portland {OR}"),
  MS_STRING("Porto"),
  MS_STRING("Prague"),
  MS_STRING("Praia"),
  MS_STRING("Pretoria"),
  MS_STRING("Pyongyang"),
  MS_STRING("Rabat"),
  MS_STRING("Rangpur"),
  MS_STRING("Reggane"),
  MS_STRING("Reykjavík"),
  MS_STRING("Riga"),
  MS_STRING("Riyadh"),
  MS_STRING("Rome"),
  MS_STRING("Roseau"),
  MS_STRING("Rostov-on-Don"),
  MS_STRING("Sacramento"),
  MS_STRING("Saint Petersburg"),
  MS_STRING("Saint-Pierre"),
  MS_STRING("Salt Lake City"),
  MS_STRING("San Antonio"),
  MS_STRING("San Diego"),
  MS_STRING("San Francisco"),
  MS_STRING("San Jose"),
  MS_STRING("San José"),
  MS_STRING("San Juan"),
  MS_STRING("San Salvador"),
  MS_STRING("Sana'a"),
  MS_STRING("Santo Domingo"),
  MS_STRING("Sapporo"),
  MS_STRING("Sarajevo"),
  MS_STRING("Saskatoon"),
  MS_STRING("Seattle"),
  MS_STRING("Ségou"),
  MS_STRING("Seoul"),
  MS_STRING("Seville"),
  MS_STRING("Shanghai"),
  MS_STRING("Singapore"),
  MS_STRING("Skopje"),
  MS_STRING("Sochi"),
  MS_STRING("Sofia"),
  MS_STRING("Sokoto"),
  MS_STRING("Split"),
  MS_STRING("St. John's"),
  MS_STRING("St. Louis"),
  MS_STRING("Stockholm"),
  MS_STRING("Surabaya"),
  MS_STRING("Suva"),
  MS_STRING("Suwałki"),
  MS_STRING("Sydney"),
  MS_STRING("Tabora"),
  MS_STRING("Tabriz"),
  MS_STRING("Taipei"),
  MS_STRING("Tallinn"),
  MS_STRING("Tamale"),
  MS_STRING("Tamanrasset"),
  MS_STRING("Tampa"),
  MS_STRING("Tashkent"),
  MS_STRING("Tauranga"),
  MS_STRING("Tbilisi"),
  MS_STRING("Tegucigalpa"),
  MS_STRING("Tehran"),
  MS_STRING("Tel Aviv"),
  MS_STRING("Thessaloniki"),
  MS_STRING("Thiès"),
  MS_STRING("Tijuana"),
  MS_STRING("Timbuktu"),
  MS_STRING("Tirana"),
  MS_STRING("Toamasina"),
  MS_STRING("Tokyo"),
  MS_STRING("Toliara"),
  MS_STRING("Toluca"),
  MS_STRING("Toronto"),
  MS_STRING("Tripoli"),
  MS_STRING("Tromsø"),
  MS_STRING("Tucson"),
  MS_STRING("Tunis"),
  MS_STRING("Ulaanbaatar"),
  MS_STRING("Upington"),
  MS_STRING("Ürümqi"),
  MS_STRING("Vaduz"),
  MS_STRING("Valencia"),
  MS_STRING("Valletta"),
  MS_STRING("Vancouver"),
  MS_STRING("Veracruz"),
  MS_STRING("Vienna"),
  MS_STRING("Vientiane"),
  MS_STRING("Villahermosa"),
  MS_STRING("Vilnius"),
  MS_STRING("Virginia Beach"),
  MS_STRING("Vladivostok"),
  MS_STRING("Warsaw"),
  MS_STRING("Washington, D.C."),
  MS_STRING("Wau"),
  MS_STRING("Wellington"),
  MS_STRING("Whitehorse"),
  MS_STRING("Wichita"),
  MS_STRING("Willemstad"),
  MS_STRING("Winnipeg"),
  MS_STRING("Wrocław"),
  MS_STRING("Xi'an"),
  MS_STRING("Yakutsk"),
  MS_STRING("Yangon"),
  MS_STRING("Yaoundé"),
  MS_STRING("Yellowknife"),
  MS_STRING("Yerevan"),
  MS_STRING("Yinchuan"),
  MS_STRING("Zagreb"),
  MS_STRING("Zanzibar City"),
  MS_STRING("Zürich"),
};

#define MAX_LINE_COUNT_LG2 25
#define MAX_LINE_COUNT (1ULL << MAX_LINE_COUNT_LG2)
#define MAX_STRING_LEN_LG2 7

static u64
FNV1A(u8* data, u32 len)
{
  u64 hash = 14695981039346656037;
  for (u32 i = 0; i < len; ++i)
  {
    hash ^= data[i];
    hash *= 1099511628211;
  }

  return hash;
}

static u64
Hash(u8* data, u32 len)
{
  return FNV1A(data, len);
}

#define REF_TABLE_SIZE_LG2 15
#define REF_TABLE_SIZE (1ULL << REF_TABLE_SIZE_LG2)
#define REF_TABLE_MASK (REF_TABLE_SIZE-1)
#define REF_TABLE_STRING_STORAGE_CAP_LG2 (MAX_LINE_COUNT_LG2 + MAX_STRING_LEN_LG2)
#define REF_TABLE_STRING_STORAGE_CAP (1ULL << REF_TABLE_STRING_STORAGE_CAP_LG2)

typedef struct Ref_Table_Entry
{
  u64 hash;
  u32 offset;
  u32 len;
  s16 min;
  s16 max;
  u32 count;
  s64 acc;
} Ref_Table_Entry;

typedef struct Ref_Table
{
  u32 entry_count;
  u32 string_cur;
  Ref_Table_Entry* entries;
  u8* strings;
} Ref_Table;

// TODO: What to do about page faults?
static Ref_Table
RefTable_Create()
{
  Ref_Table_Entry* entries = VirtualAlloc(0, REF_TABLE_SIZE*sizeof(Ref_Table_Entry), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
  u8* strings              = VirtualAlloc(0, REF_TABLE_STRING_STORAGE_CAP*sizeof(Ref_Table_Entry), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);

  return (Ref_Table){
    .entry_count = 0,
    .string_cur  = 0,
    .entries     = entries,
    .strings     = strings,
  };
}

static Ref_Table_Entry*
RefTable_Put(Ref_Table* table, u8* data, u32 len)
{
  u64 hash = Hash(data, len);
  u64 idx  = hash & REF_TABLE_MASK;
  u64 step = 1;

  hash |= 1;

  while (table->entries[idx].hash != 0)
  {
    if (table->entries[idx].hash == hash)
    {
      bool does_match = (table->entries[idx].len == len);

      u8* entry_string = table->strings + table->entries[idx].offset;
      for (u32 i = 0; i < table->entries[idx].len && does_match; ++i) does_match = (entry_string[i] == data[i]);

      if (does_match) break;
    }

    idx = (idx + step++) & REF_TABLE_MASK;
  }

  if (table->entries[idx].hash == 0)
  {
    table->entries[idx] = (Ref_Table_Entry){
      .hash   = hash,
      .offset = table->string_cur,
      .len    = len,
      .min    = 0x7FFF,
      .max    = 0,
      .count  = 0,
      .acc    = 0,
    };

    memcpy(table->strings + table->string_cur, data, len);
    table->string_cur += len;

    table->entry_count += 1;
  }

  return &table->entries[idx];
}

int
main(int argc, char** argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Invalid Arguments. Usage: hashbench [number of test lines]\n");
    return -1;
  }

  u32 num_lines = 0;
  for (u8* scan = argv[1]; *scan != 0; ++scan)
  {
    num_lines = num_lines*10 + (*scan&0xF);

    if ((u8)(*scan - '0') > (u8)9 || num_lines > MAX_LINE_COUNT)
    {
      fprintf(stderr, "Illegal number of lines, must be a positive integer less than %llu\n", MAX_LINE_COUNT);
      return -1;
    }
  }

  String* lines = VirtualAlloc(0, num_lines*sizeof(String), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

  srand((u32)time(0));
  for (u32 i = 0; i < num_lines; ++i)
  {
    lines[i] = WeatherStations[rand() % ARRAY_SIZE(WeatherStations)];
  }

  u64 start = __rdtsc();

  Ref_Table table = RefTable_Create();

  for (u32 i = 0; i < num_lines; ++i)
  {
    Ref_Table_Entry* entry = RefTable_Put(&table, lines[i].data, lines[i].len);
    entry->count += 1;
  }

  u64 end = __rdtsc();

  printf("finished processing %u lines in: %llu ticks\n", num_lines, end - start);

  return 0;
}
