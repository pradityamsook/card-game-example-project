#!/bin/bash
set -e

echo "Waiting for the PostgreSQL to be start..."
until docker-compose exec db pg_isready -U admin -d myapp; do
  sleep 1
done

echo "Running migrations..."
docker-compose exec db psql -U admin -d myapp -f /migrations/001_create_table_card_table.sql
docker-compose exec db psql -U admin -d myapp -f /migrations/0001_create_table_users_table.sql
echo "Migrations completed."