//
//  KBDataImporter.m
//  KegPad
//
//  Created by Gabriel Handford on 8/9/10.
//  Copyright 2010 Yelp. All rights reserved.
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#import "KBDataImporter.h"

#import "KBApplication.h"

#import "YAJL.h"
#import "GHNSBundle+Utils.h"
#import "GHNSDictionary+NSNull.h"

@implementation KBDataImporter

- (id)JSONFromResource:(NSString *)resource {
  NSLog(@"Parsing resource: %@", resource);
  NSError *error = nil;
  id JSONValue = [[[NSBundle mainBundle] gh_loadStringDataFromResource:resource] yajl_JSONWithOptions:YAJLParserOptionsAllowComments error:&error];
  if (error) [NSException raise:NSGenericException format:[error localizedDescription], nil];
  return JSONValue;
}

- (void)updateUsersInDataStore:(KBDataStore *)dataStore {
  NSError *error = nil;
  NSArray *users = [self JSONFromResource:@"users.json"];
  for (NSDictionary *user in users) {
    [dataStore addOrUpdateUserWithRFID:[user gh_objectMaybeNilForKey:@"rfid"]
                           displayName:[user gh_objectMaybeNilForKey:@"display_name"]
                                 error:&error];
    KBDataStoreCheckError(error);
  }
}

- (void)updateBeersInDataStore:(KBDataStore *)dataStore {
  NSError *error = nil;
  NSArray *beers = [self JSONFromResource:@"beers.json"];
  for (NSDictionary *beer in beers) {
    [dataStore updateBeerWithId:[beer gh_objectMaybeNilForKey:@"id"]
                           name:[beer gh_objectMaybeNilForKey:@"name"]
                           info:[beer gh_objectMaybeNilForKey:@"info"]
                           type:[beer gh_objectMaybeNilForKey:@"type"]
                        country:[beer gh_objectMaybeNilForKey:@"country"]
                      imageName:[beer gh_objectMaybeNilForKey:@"image"]
                            abv:[[beer gh_objectMaybeNilForKey:@"abv"] floatValue]
                          error:&error];
    KBDataStoreCheckError(error);
  }
}

- (void)updateKegsInDataStore:(KBDataStore *)dataStore {
  NSError *error = nil;
  NSArray *kegs = [self JSONFromResource:@"kegs.json"];
  NSLog(@"kegs=%@", kegs);
  for (NSDictionary *keg in kegs) {
    NSString *beerId = [keg gh_objectMaybeNilForKey:@"beer_id"];
    KBBeer *beer = [dataStore beerWithId:beerId error:nil];
    NSAssert1(beer, @"Beer with id: \"%@\" not found", beerId);
    [dataStore addOrUpdateKegWithId:[keg gh_objectMaybeNilForKey:@"id"]
                               beer:beer
                     volumeAdjusted:[[keg gh_objectMaybeNilForKey:@"volume_adjusted"] floatValue]
                        volumeTotal:[[keg gh_objectMaybeNilForKey:@"volume_total"] floatValue]
                              error:&error];
    KBDataStoreCheckError(error);
  }
}

+ (void)updateDataStore:(KBDataStore *)dataStore {
  NSParameterAssert(dataStore);
  KBDataImporter *importer = [[KBDataImporter alloc] init];
  [importer updateUsersInDataStore:dataStore];
  [importer updateBeersInDataStore:dataStore];
  [importer updateKegsInDataStore:dataStore];
  
  // If we don't have a selected keg then lets select the first one
  if (![dataStore kegAtPosition:0]) {
    NSError *error = nil;
    KBKeg *keg = [[dataStore kegsWithOffset:0 limit:1 error:&error] gh_firstObject];
    KBDataStoreCheckError(error);
    NSAssert(keg, @"No keg could be selected");
    [dataStore setKeg:keg position:0];
    NSLog(@"Auto selecting keg: %@", keg);
  }
  
  [importer release];
}
 
@end
