//
//  KBDataStore.h
//  KegPad
//
//  Created by Gabriel Handford on 7/28/10.
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

#import <CoreData/CoreData.h>

#import "KBKeg.h"
#import "KBUser.h"
#import "KBBeer.h"
#import "KBKegProcessing.h"

#define KBDataStoreCheckError(__ERROR__) do { \
  if (error) NSLog(@"Error: %@; %@", error, [error localizedFailureReason]); \
} while(0)


/*!
 Main data store (CoreData).
 */
@interface KBDataStore : NSObject {
  
@private
  NSManagedObjectContext *managedObjectContext_;
  NSManagedObjectModel *managedObjectModel_;
  NSPersistentStoreCoordinator *persistentStoreCoordinator_;
  
}

/*!
 Save.
 @param error Out error
 @result YES if saved
 */
- (BOOL)save:(NSError **)error;

/*!
 Returns the managed object context for the application.
 If the context doesn't already exist, it is created and bound to the persistent store coordinator for the application.
 */
- (NSManagedObjectContext *)managedObjectContext;

/*!
 Returns the managed object model for the application.
 If the model doesn't already exist, it is created from the application's model.
 */
- (NSManagedObjectModel *)managedObjectModel;

/*!
 Returns the persistent store coordinator for the application.
 If the coordinator doesn't already exist, it is created and the application's store added to it.
 */
- (NSPersistentStoreCoordinator *)persistentStoreCoordinator;

/*!
 Documents directory, where the data store is persisted.
 */
- (NSString *)applicationDocumentsDirectory;

/*!
 Set the keg at position.
 */
- (void)setKeg:(KBKeg *)keg position:(NSInteger)position;

/*!
 Get the key at position.
 */
- (KBKeg *)kegAtPosition:(NSInteger)position;

/*!
 Get beer with identifier.
 @param id identifier
 @param error Out error
 @result Beer
 */
- (KBBeer *)beerWithId:(NSString *)id error:(NSError **)error;

/*!
 Add a keg with beer.
 @param beer Beer
 @param error Out error
 @result YES if keg was added
 */
- (BOOL)addKegWithBeer:(KBBeer *)beer error:(NSError **)error;

/*!
 Update beer with identifier.
 @param id Identifier
 @param name Name ("Stella Artois")
 @param info Description to set ("A pilsner ...")
 @param type Beer type ("Lager / Pilsner")
 @param country Country description ("Belgium")
 @param imageName Name of image in resources
 @param abv Alchohol by volume
 @param error Out error
 @result YES if beer was updated
 */
- (BOOL)updateBeerWithId:(NSString *)id name:(NSString *)name info:(NSString *)info type:(NSString *)type country:(NSString *)country 
imageName:(NSString *)imageName abv:(float)abv error:(NSError **)error;

/*!
 Add a keg temperature value.
 @param temperature Temperature in celcius
 @param keg Keg
 @param error Out error
 @result YES if keg temperature was added
 */
- (BOOL)addKegTemperature:(float)temperature keg:(KBKeg *)keg error:(NSError **)error;

/*!
 Add a keg pour.
 @param amount Amount in liters
 @param keg Keg
 @param user User, if nil is anonymous
 @param error Out error
 @result YES if keg pour was added
 */
- (BOOL)addKegPour:(float)amount keg:(KBKeg *)keg user:(KBUser *)user error:(NSError **)error;

/*!
 Get a list of recent keg pours.
 @param limit Max number of pours
 @param ascending Ascending
 @param error Out error
 @result List of keg pours
 */
- (NSArray */*of KBKegPour*/)recentKegPours:(NSUInteger)limit ascending:(BOOL)ascending error:(NSError **)error;

/*!
 Get last keg pour.
 @param error Out error
 @result Last keg pour
 */
- (KBKegPour *)lastPour:(NSError **)error;

/*!
 Add/update a user.
 @param rfid RFID
 @param displayName Display name
 @param error Out error
 @result YES if user was added
 */
- (BOOL)addOrUpdateUserWithRFID:(NSString *)RFID displayName:(NSString *)displayName error:(NSError **)error;

/*!
 Find user by RFID.
 @param rfid RFID
 @param error Out error
 */
- (KBUser *)userWithRFID:(NSString *)rfid error:(NSError **)error;

/*!
 Get a list of kegs.
 @param offset Offset
 @param limit limit
 @param error Out error
 @result List of kegs
 */
- (NSArray */*of KBKeg*/)kegsWithOffset:(NSUInteger)offset limit:(NSUInteger)limit error:(NSError **)error;

/*!
 Keg by id.
 @param id Identifier
 @param error Out error
 @result Keg
 */
- (KBKeg *)kegWithId:(NSString *)id error:(NSError **)error;

/*!
 Add/update keg information for id.
 @param id
 @param beer
 @param volumeAdjusted Volume in liters to adjust (subtract) the keg volume; This value with poured value and total value determines how much is remaining
 @param volumeTotal
 @param error Out error
 @result YES if added or updated
 */
- (BOOL)addOrUpdateKegWithId:(NSString *)id beer:(KBBeer *)beer volumeAdjusted:(float)volumeAdjusted volumeTotal:(float)volumeTotal error:(NSError **)error;

/*!
 Get list of users.
 @param offset Offset
 @param limit Limit
 @param error Out error
 @result List of users
 */
- (NSArray *)usersWithOffset:(NSUInteger)offset limit:(NSUInteger)limit error:(NSError **)error;

/*!
 Get top users (by pour).
 @param offset Offset
 @param limit Limit
 @param error Out error
 */
- (NSArray *)topUsersByPourWithOffset:(NSUInteger)offset limit:(NSUInteger)limit error:(NSError **)error;

/*!
 Get recent keg pours from date range for user (or all users).
 @param fromData
 @param toDate
 @param user User, if nil then will query all users
 @param error Out error
 @result List of keg pours
 */
- (NSArray */*of KBKegPour*/)recentKegPoursFromDate:(NSDate *)fromDate toDate:(NSDate *)toDate user:(KBUser *)user error:(NSError **)error;

/*!
 Get the rate for keg pours in the last hour for user.
 @param user User, if nil will query for all users
 @param error Out error
 */
- (float)rateForKegPoursLastHourForUser:(KBUser *)user error:(NSError **)error;

/*!
 For all stats to recompute.
 */
- (void)recomputeStats;

@end
